#include "OPGameModeBase.h"
#include "Character/Player/OPPlayerCharacter.h"
#include "Framework/OPPlayerController.h"
#include "HUD/OPHUD.h"
#include "Engine/Engine.h"

AOPGameModeBase::AOPGameModeBase()
{
	DefaultPawnClass = AOPPlayerCharacter::StaticClass();
	PlayerControllerClass = AOPPlayerController::StaticClass();
	HUDClass = AOPHUD::StaticClass();
}

void AOPGameModeBase::RequestGameClear(AActor* InstigatorActor)
{
    if (GameResult != EOPGameResult::None)
    {
        return;
    }

    BroadcastGameResult(EOPGameResult::Cleared, InstigatorActor);
}

void AOPGameModeBase::RequestGameOver(AActor* InstigatorActor)
{
    if (GameResult != EOPGameResult::None)
    {
        return;
    }

    BroadcastGameResult(EOPGameResult::GameOver, InstigatorActor);
}

void AOPGameModeBase::BroadcastGameResult(EOPGameResult InResult, AActor* InstigatorActor)
{
    GameResult = InResult;
    OnGameResult.Broadcast(GameResult, InstigatorActor);
}