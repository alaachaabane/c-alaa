#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealDriveRoadActor.generated.h"

UCLASS()
class REALDRIVE_API ARealDriveRoadActor : public AActor
{
    GENERATED_BODY()
public:
    ARealDriveRoadActor();
protected:
    virtual void OnConstruction(const FTransform& Transform) override;
private:
    UPROPERTY(VisibleAnywhere) TObjectPtr<class UProceduralMeshComponent> RoadMesh;
    void BuildRoad();
};
