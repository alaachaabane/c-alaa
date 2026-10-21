#include "RealDriveGameMode.h"
#include "RealDriveRoadActor.h"
#include "RealDriveVehiclePawn.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

ARealDriveGameMode::ARealDriveGameMode()
{
    DefaultPawnClass = ARealDriveVehiclePawn::StaticClass();
}

void ARealDriveGameMode::StartPlay()
{
    Super::StartPlay();
    UWorld* World = GetWorld();
    if (!World) return;
    World->SpawnActor<ARealDriveRoadActor>(ARealDriveRoadActor::StaticClass(),FVector(-5000.f,0.f,0.f),FRotator::ZeroRotator);
    const FVector Start(0.f,380.f,155.f);
    ARealDriveVehiclePawn* Car = World->SpawnActor<ARealDriveVehiclePawn>(ARealDriveVehiclePawn::StaticClass(),Start,FRotator(0.f,-3.f,0.f));
    if (Car)
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            if (APawn* PreviousPawn = PC->GetPawn()) PreviousPawn->Destroy();
            PC->Possess(Car);
            PC->SetShowMouseCursor(false);
            PC->SetInputMode(FInputModeGameOnly());
        }
    }
}
