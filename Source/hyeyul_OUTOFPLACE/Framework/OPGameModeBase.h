#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OPGameModeBase.generated.h"

class AActor;

UENUM(BlueprintType)
enum class EOPGameResult : uint8
{
    None,
    Cleared,
    GameOver
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOPGameResult, EOPGameResult /*Result*/, AActor* /*InstigatorActor*/);

UCLASS()
class HYEYUL_OUTOFPLACE_API AOPGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AOPGameModeBase();

    void RequestGameClear(AActor* InstigatorActor);
    void RequestGameOver(AActor* InstigatorActor);

    EOPGameResult GetGameResult() const { return GameResult; }

    const FOnOPGameResult& GetOnGameResult() const { return OnGameResult; }
    FOnOPGameResult& GetOnGameResult() { return OnGameResult; }

private:
    void BroadcastGameResult(EOPGameResult InResult, AActor* InstigatorActor);

private:
    EOPGameResult GameResult = EOPGameResult::None;
    FOnOPGameResult OnGameResult;
};