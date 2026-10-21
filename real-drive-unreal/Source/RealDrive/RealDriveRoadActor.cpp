#include "RealDriveRoadActor.h"
#include "ProceduralMeshComponent.h"
#include "Materials/Material.h"

ARealDriveRoadActor::ARealDriveRoadActor()
{
    PrimaryActorTick.bCanEverTick = false;
    RoadMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Road"));
    SetRootComponent(RoadMesh);
    RoadMesh->SetCollisionProfileName(TEXT("BlockAll"));
    RoadMesh->bUseAsyncCooking = false;
    RoadMesh->SetMaterial(0, UMaterial::GetDefaultMaterial(MD_Surface));
}

void ARealDriveRoadActor::OnConstruction(const FTransform& Transform) { BuildRoad(); }

void ARealDriveRoadActor::BuildRoad()
{
    constexpr int32 Segments = 640;
    constexpr float Step = 500.f;
    constexpr float HalfWidth = 650.f;
    TArray<FVector> V;
    TArray<int32> I;
    TArray<FVector> N;
    TArray<FVector2D> UV;
    TArray<FColor> Colors;
    V.Reserve((Segments + 1) * 2); I.Reserve(Segments * 6);
    auto Center = [](float X) { return 480.f * FMath::Sin(X / 6200.f) + 180.f * FMath::Sin(X / 1700.f); };
    for (int32 S = 0; S <= Segments; ++S)
    {
        const float X = S * Step;
        const float Y = Center(X);
        V.Add(FVector(X, Y - HalfWidth, 0.f)); V.Add(FVector(X, Y + HalfWidth, 0.f));
        UV.Add(FVector2D(S * 0.8f, 0)); UV.Add(FVector2D(S * 0.8f, 1));
        Colors.Add(FColor(48,51,51,255)); Colors.Add(FColor(48,51,51,255));
        if (S < Segments) { const int32 A=S*2, B=A+1, C=A+2, D=A+3; I.Add(A); I.Add(C); I.Add(B); I.Add(B); I.Add(C); I.Add(D); }
    }
    N.SetNum(V.Num());
    for (int32 S = 0; S <= Segments; ++S)
    {
        const float X=S*Step;
        const float DY=480.f/6200.f*FMath::Cos(X/6200.f)+180.f/1700.f*FMath::Cos(X/1700.f);
        const FVector Normal=FVector(-DY,0.f,1.f).GetSafeNormal();
        N[S*2]=Normal; N[S*2+1]=Normal;
    }
    RoadMesh->ClearAllMeshSections();
    RoadMesh->CreateMeshSection(0,V,I,N,UV,Colors,TArray<FProcMeshTangent>(),true);
}
