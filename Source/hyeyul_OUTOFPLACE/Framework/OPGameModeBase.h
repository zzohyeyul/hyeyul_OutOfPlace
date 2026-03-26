#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OPGameModeBase.generated.h"

class AActor;

UENUM()
enum class EOPGameResult : uint8
{
	None,
	Cleared,
	GameOver
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameResult, EOPGameResult /*Result*/, AActor* /*Instigator*/);

UCLASS()
class HYEYUL_OUTOFPLACE_API AOPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOPGameModeBase();

	void RequestGameClear(AActor* InstigatorActor);
	void RequestGameOver(AActor* InstigatorActor);

	EOPGameResult GetGameResult() const { return GameResult; }

private:
	EOPGameResult GameResult = EOPGameResult::None;
	FOnGameResult OnGameResult;

	void SetGameResult(EOPGameResult NewResult, AActor* InstigatorActor);
};