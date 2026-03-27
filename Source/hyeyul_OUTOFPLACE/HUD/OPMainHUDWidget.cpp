#include "HUD/OPMainHUDWidget.h"

#include "Components/TextBlock.h"

void UOPMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CacheInventorySlotTexts();
}

void UOPMainHUDWidget::CacheInventorySlotTexts()
{
	InventorySlotTexts.Reset();

	InventorySlotTexts.Add(InventorySlotText_0);
	InventorySlotTexts.Add(InventorySlotText_1);
	InventorySlotTexts.Add(InventorySlotText_2);
	InventorySlotTexts.Add(InventorySlotText_3);
}

void UOPMainHUDWidget::UpdateInventory(const TArray<FName>& ItemIds, int32 Capacity)
{
	const int32 SlotCount = FMath::Min(Capacity, InventorySlotTexts.Num());

	for (int32 Index = 0; Index < SlotCount; ++Index)
	{
		UTextBlock* SlotText = InventorySlotTexts[Index];
		if (!SlotText)
		{
			continue;
		}

		if (ItemIds.IsValidIndex(Index))
		{
			SlotText->SetText(FText::FromName(ItemIds[Index]));
			continue;
		}

		SlotText->SetText(FText::FromString(TEXT("- Empty -")));
	}
}

void UOPMainHUDWidget::UpdateInteractionPrompt(const FText& PromptText)
{
	if (!InteractionPromptText)
	{
		return;
	}

	InteractionPromptText->SetText(PromptText);
}