#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RealDriveGameMode.generated.h"

UCLASS()
class REALDRIVE_API ARealDriveGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ARealDriveGameMode();
    virtual void StartPlay() override;
};
