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
	SetGameResult(EOPGameResult::Cleared, InstigatorActor);
}

void AOPGameModeBase::RequestGameOver(AActor* InstigatorActor)
{
	SetGameResult(EOPGameResult::GameOver, InstigatorActor);
}

void AOPGameModeBase::SetGameResult(EOPGameResult NewResult, AActor* InstigatorActor)
{
	if (GameResult != EOPGameResult::None) return;

	GameResult = NewResult;

	OnGameResult.Broadcast(GameResult, InstigatorActor);

#if UE_BUILD_DEVELOPMENT
	if (GEngine)
	{
		const FString Msg = (GameResult == EOPGameResult::Cleared)
			? TEXT("[GameMode] CLEARED")
			: TEXT("[GameMode] GAME OVER");
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Msg);
	}
#endif
}