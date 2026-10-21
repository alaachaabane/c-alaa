#include "RealDriveVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"

ARealDriveVehiclePawn::ARealDriveVehiclePawn()
{
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cylinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    Chassis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chassis"));
    SetRootComponent(Chassis);
    if (Cube.Succeeded()) Chassis->SetStaticMesh(Cube.Object);
    Chassis->SetRelativeScale3D(FVector(4.3f, 1.9f, .5f));
    Chassis->SetSimulatePhysics(true);
    Chassis->SetMassOverrideInKg(NAME_None, 1450.f, true);
    Chassis->SetLinearDamping(.035f);
    Chassis->SetAngularDamping(1.35f);
    Chassis->SetCollisionProfileName(TEXT("PhysicsActor"));
    Chassis->BodyInstance.bUseCCD = true;
    Cabin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cabin"));
    Cabin->SetupAttachment(Chassis);
    if (Cube.Succeeded()) Cabin->SetStaticMesh(Cube.Object);
    Cabin->SetRelativeScale3D(FVector(1.7f,1.35f,.62f));
    Cabin->SetRelativeLocation(FVector(-5.f,0.f,54.f));
    Cabin->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ChaseArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ChaseArm"));
    ChaseArm->SetupAttachment(Chassis);
    ChaseArm->TargetArmLength = 620.f;
    ChaseArm->SetRelativeLocation(FVector(-70.f, 0.f, 175.f));
    ChaseArm->SetRelativeRotation(FRotator(-9.f, 0.f, 0.f));
    ChaseArm->bEnableCameraLag = true;
    ChaseArm->CameraLagSpeed = 5.5f;
    ChaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCamera"));
    ChaseCamera->SetupAttachment(ChaseArm);

    CockpitCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CockpitCamera"));
    CockpitCamera->SetupAttachment(Chassis);
    CockpitCamera->SetRelativeLocation(FVector(42.f, 0.f, 102.f));
    CockpitCamera->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    CockpitCamera->SetActive(false);

    WheelMounts[0] = FVector(142.f, -94.f, -40.f); WheelMounts[1] = FVector(142.f, 94.f, -40.f);
    WheelMounts[2] = FVector(-142.f, -94.f, -40.f); WheelMounts[3] = FVector(-142.f, 94.f, -40.f);
    for (int32 i=0;i<4;++i)
    {
        UStaticMeshComponent* Wheel = CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("Wheel%d"),i));
        Wheel->SetupAttachment(Chassis);
        if (Cylinder.Succeeded()) Wheel->SetStaticMesh(Cylinder.Object);
        Wheel->SetRelativeScale3D(FVector(.38f,.38f,.17f));
        Wheel->SetRelativeRotation(FRotator(0.f,90.f,0.f));
        Wheel->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Wheel->SetSimulatePhysics(false);
        WheelVisuals.Add(Wheel);
    }
}

void ARealDriveVehiclePawn::BeginPlay() { Super::BeginPlay(); }

void ARealDriveVehiclePawn::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis(TEXT("Throttle"), this, &ARealDriveVehiclePawn::SetThrottle);
    Input->BindAxis(TEXT("Steer"), this, &ARealDriveVehiclePawn::SetSteer);
    Input->BindAxis(TEXT("Brake"), this, &ARealDriveVehiclePawn::SetBrake);
    Input->BindAction(TEXT("Camera"), IE_Pressed, this, &ARealDriveVehiclePawn::ToggleCamera);
    Input->BindAction(TEXT("Reset"), IE_Pressed, this, &ARealDriveVehiclePawn::ResetVehicle);
}

void ARealDriveVehiclePawn::Tick(float Dt)
{
    Super::Tick(Dt);
    if (!Chassis || !Chassis->IsSimulatingPhysics()) return;
    const FVector Up = Chassis->GetUpVector();
    const FVector BaseForward = Chassis->GetForwardVector();
    const FVector Velocity = Chassis->GetPhysicsLinearVelocity();
    SpeedKmh = FVector::DotProduct(Velocity, BaseForward) * .036f;
    const float SteerAngle = Steer * 29.f;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(RealDriveSuspension), false, this);
    const float RestLength = 82.f, SpringK = 56000.f, Damper = 6500.f, WheelRadius = 38.f;

    for (int32 i=0;i<4;++i)
    {
        const FVector Mount = Chassis->GetComponentTransform().TransformPosition(WheelMounts[i]);
        const FVector Start = Mount + Up*16.f;
        const FVector End = Mount - Up*100.f;
        FHitResult Hit;
        const bool bGrounded = GetWorld()->LineTraceSingleByChannel(Hit,Start,End,ECC_Visibility,Params);
        FVector VisualPosition = Mount - Up*RestLength;
        if (bGrounded)
        {
            const float Travel = FVector::Distance(Mount,Hit.ImpactPoint);
            const float Compression = FMath::Clamp(RestLength-Travel,0.f,42.f);
            const float SuspensionSpeed = FVector::DotProduct(Chassis->GetPhysicsLinearVelocityAtPoint(Hit.ImpactPoint),Hit.ImpactNormal);
            const float NormalForce = FMath::Clamp(Compression*SpringK*.01f-SuspensionSpeed*Damper*.01f,0.f,19000.f);
            Chassis->AddForceAtLocation(Hit.ImpactNormal*NormalForce,Hit.ImpactPoint);
            FVector Forward = BaseForward;
            if (i<2) Forward = Forward.RotateAngleAxis(SteerAngle,Up);
            const FVector Right = FVector::CrossProduct(Up,Forward).GetSafeNormal();
            const FVector ContactVelocity = Chassis->GetPhysicsLinearVelocityAtPoint(Hit.ImpactPoint);
            const float LongSpeed = FVector::DotProduct(ContactVelocity,Forward);
            const float SideSpeed = FVector::DotProduct(ContactVelocity,Right);
            const float Grip = 1.12f;
            const float SideForce = FMath::Clamp(-SideSpeed*.01f*8400.f,-NormalForce*Grip,NormalForce*Grip);
            float LongForce = 0.f;
            if (i>=2) LongForce += Throttle*6100.f;
            LongForce -= FMath::Sign(LongSpeed)*Brake*15000.f;
            LongForce = FMath::Clamp(LongForce,-NormalForce*Grip,NormalForce*Grip);
            Chassis->AddForceAtLocation(Forward*LongForce+Right*SideForce,Hit.ImpactPoint);
            VisualPosition = Hit.ImpactPoint + Hit.ImpactNormal*WheelRadius;
        }
        if (WheelVisuals.IsValidIndex(i))
        {
            WheelVisuals[i]->SetWorldLocation(VisualPosition);
            const FRotator SteeringRotation(0.f,i<2?SteerAngle:0.f,0.f);
            WheelVisuals[i]->SetWorldRotation(Chassis->GetComponentRotation()+SteeringRotation+FRotator(0.f,90.f,0.f));
        }
    }
    Chassis->AddForce(-Velocity.GetSafeNormal()*Velocity.SizeSquared()*.0001f);
}

void ARealDriveVehiclePawn::ToggleCamera()
{
    bCockpit = !bCockpit;
    ChaseCamera->SetActive(!bCockpit);
    CockpitCamera->SetActive(bCockpit);
}

void ARealDriveVehiclePawn::ResetVehicle()
{
    const FVector P = GetActorLocation();
    Chassis->SetPhysicsLinearVelocity(FVector::ZeroVector);
    Chassis->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
    Chassis->SetWorldLocationAndRotation(FVector(P.X,P.Y,180.f),FRotator(0.f,GetActorRotation().Yaw,0.f),false,nullptr,ETeleportType::TeleportPhysics);
}
