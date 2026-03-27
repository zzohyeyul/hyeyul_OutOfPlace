#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Framework/OPGameModeBase.h"
#include "OPHUD.generated.h"

class UOPMainHUDWidget;
class UOPResultWidget;
class UOPInventoryComponent;
class UOPInteractionComponent;

UCLASS()
class HYEYUL_OUTOFPLACE_API AOPHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void InitializeWidgets();
	void BindPlayerData();
	void BindGameMode();
	void UnbindAll();

	void HandleInventoryChanged();
	void HandleInteractionPromptChanged(const FText& PromptText);
	void HandleGameResult(EOPGameResult Result, AActor* InstigatorActor);

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UOPMainHUDWidget> MainHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UOPResultWidget> ResultWidgetClass;

	UPROPERTY()
	TObjectPtr<UOPMainHUDWidget> MainHUDWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UOPResultWidget> ResultWidget = nullptr;

	TWeakObjectPtr<UOPInventoryComponent> BoundInventoryComp;
	TWeakObjectPtr<UOPInteractionComponent> BoundInteractionComp;
	TWeakObjectPtr<AOPGameModeBase> CachedGameMode;
};