#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OPMainHUDWidget.generated.h"

class UCanvasPanel;
class UHorizontalBox;
class UTextBlock;

UCLASS()
class HYEYUL_OUTOFPLACE_API UOPMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	void UpdateInventory(const TArray<FName>& ItemIds, int32 Capacity);
	void UpdateInteractionPrompt(const FText& PromptText);

private:
	void BuildInventorySlots(int32 SlotCount);

private:
	UPROPERTY()
	TObjectPtr<UCanvasPanel> RootCanvas = nullptr;

	UPROPERTY()
	TObjectPtr<UHorizontalBox> InventoryBox = nullptr;

	UPROPERTY()
	TObjectPtr<UTextBlock> InteractionPromptText = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UTextBlock>> InventorySlotTexts;
};