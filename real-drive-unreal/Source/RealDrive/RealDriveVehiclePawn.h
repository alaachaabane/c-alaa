#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RealDriveVehiclePawn.generated.h"

UCLASS()
class REALDRIVE_API ARealDriveVehiclePawn : public APawn
{
    GENERATED_BODY()
public:
    ARealDriveVehiclePawn();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void SetThrottle(float Value) { Throttle = FMath::Clamp(Value, -1.f, 1.f); }
    void SetSteer(float Value) { Steer = FMath::Clamp(Value, -1.f, 1.f); }
    void SetBrake(float Value) { Brake = FMath::Clamp(Value, 0.f, 1.f); }
    void ToggleCamera();
    void ResetVehicle();
protected:
    virtual void BeginPlay() override;
private:
    UPROPERTY(VisibleAnywhere) TObjectPtr<class UStaticMeshComponent> Chassis;
    UPROPERTY(VisibleAnywhere) TObjectPtr<class UStaticMeshComponent> Cabin;
    UPROPERTY(VisibleAnywhere) TObjectPtr<class USpringArmComponent> ChaseArm;
    UPROPERTY(VisibleAnywhere) TObjectPtr<class UCameraComponent> ChaseCamera;
    UPROPERTY(VisibleAnywhere) TObjectPtr<class UCameraComponent> CockpitCamera;
    UPROPERTY(VisibleAnywhere) TArray<TObjectPtr<class UStaticMeshComponent>> WheelVisuals;
    FVector WheelMounts[4];
    float Throttle = 0.f;
    float Steer = 0.f;
    float Brake = 0.f;
    float SpeedKmh = 0.f;
    bool bCockpit = false;
};
