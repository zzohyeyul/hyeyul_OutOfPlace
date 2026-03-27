#include "HUD/OPHUD.h"

#include "GameFramework/PlayerController.h"

#include "Character/Player/OPPlayerCharacter.h"
#include "Framework/OPGameModeBase.h"
#include "HUD/OPMainHUDWidget.h"
#include "HUD/OPResultWidget.h"
#include "Interaction/OPInteractionComponent.h"
#include "Items/OPInventoryComponent.h"

void AOPHUD::BeginPlay()
{
	Super::BeginPlay();

	InitializeWidgets();
	BindPlayerData();
	BindGameMode();
}

void AOPHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnbindAll();
	Super::EndPlay(EndPlayReason);
}

void AOPHUD::InitializeWidgets()
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC || !MainHUDWidgetClass)
	{
		return;
	}

	MainHUDWidget = CreateWidget<UOPMainHUDWidget>(PC, MainHUDWidgetClass);
	if (!MainHUDWidget)
	{
		return;
	}

	MainHUDWidget->AddToViewport(0);
}

void AOPHUD::BindPlayerData()
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC)
	{
		return;
	}

	AOPPlayerCharacter* PlayerCharacter = Cast<AOPPlayerCharacter>(PC->GetPawn());
	if (!PlayerCharacter)
	{
		return;
	}

	UOPInventoryComponent* InventoryComp = PlayerCharacter->GetInventoryComponent();
	UOPInteractionComponent* InteractionComp = PlayerCharacter->GetInteractionComponent();
	if (!InventoryComp || !InteractionComp || !MainHUDWidget)
	{
		return;
	}

	BoundInventoryComp = InventoryComp;
	BoundInteractionComp = InteractionComp;

	InventoryComp->GetOnInventoryChanged().AddUObject(this, &AOPHUD::HandleInventoryChanged);
	InteractionComp->GetOnInteractionPromptChanged().AddUObject(this, &AOPHUD::HandleInteractionPromptChanged);

	HandleInventoryChanged();
	HandleInteractionPromptChanged(FText::GetEmpty());
}

void AOPHUD::BindGameMode()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AOPGameModeBase* GameMode = Cast<AOPGameModeBase>(World->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}

	CachedGameMode = GameMode;
	GameMode->GetOnGameResult().AddUObject(this, &AOPHUD::HandleGameResult);
}

void AOPHUD::UnbindAll()
{
	if (BoundInventoryComp.IsValid())
	{
		BoundInventoryComp->GetOnInventoryChanged().RemoveAll(this);
	}

	if (BoundInteractionComp.IsValid())
	{
		BoundInteractionComp->GetOnInteractionPromptChanged().RemoveAll(this);
	}

	if (CachedGameMode.IsValid())
	{
		CachedGameMode->GetOnGameResult().RemoveAll(this);
	}
}

void AOPHUD::HandleInventoryChanged()
{
	if (!MainHUDWidget || !BoundInventoryComp.IsValid())
	{
		return;
	}

	MainHUDWidget->UpdateInventory(BoundInventoryComp->GetItemIds(), BoundInventoryComp->GetCapacity());
}

void AOPHUD::HandleInteractionPromptChanged(const FText& PromptText)
{
	if (!MainHUDWidget)
	{
		return;
	}

	MainHUDWidget->UpdateInteractionPrompt(PromptText);
}

void AOPHUD::HandleGameResult(EOPGameResult Result, AActor* InstigatorActor)
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC || !ResultWidgetClass)
	{
		return;
	}

	if (!ResultWidget)
	{
		ResultWidget = CreateWidget<UOPResultWidget>(PC, ResultWidgetClass);
		if (ResultWidget)
		{
			ResultWidget->AddToViewport(100);
		}
	}

	if (ResultWidget)
	{
		ResultWidget->SetGameResult(Result);
	}

	if (MainHUDWidget)
	{
		MainHUDWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	PC->SetPause(true);
	PC->bShowMouseCursor = true;
}