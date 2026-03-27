#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OPMainHUDWidget.generated.h"

class UTextBlock;

UCLASS()
class HYEYUL_OUTOFPLACE_API UOPMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateInventory(const TArray<FName>& ItemIds, int32 Capacity);
	void UpdateInteractionPrompt(const FText& PromptText);

protected:
	virtual void NativeConstruct() override;

private:
	void CacheInventorySlotTexts();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractionPromptText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InventorySlotText_0 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InventorySlotText_1 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InventorySlotText_2 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InventorySlotText_3 = nullptr;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UTextBlock>> InventorySlotTexts;
};