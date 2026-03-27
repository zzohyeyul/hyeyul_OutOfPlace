#include "HUD/OPMainHUDWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Layout/Margin.h"

TSharedRef<SWidget> UOPMainHUDWidget::RebuildWidget()
{
	WidgetTree = NewObject<UWidgetTree>(this, TEXT("MainHUDWidgetTree"));

	RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
	WidgetTree->RootWidget = RootCanvas;

	InteractionPromptText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("InteractionPromptText"));
	InteractionPromptText->SetText(FText::GetEmpty());

	UCanvasPanelSlot* PromptSlot = RootCanvas->AddChildToCanvas(InteractionPromptText);
	PromptSlot->SetAnchors(FAnchors(0.5f, 0.85f));
	PromptSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	PromptSlot->SetAutoSize(true);

	InventoryBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass(), TEXT("InventoryBox"));

	UCanvasPanelSlot* InventorySlot = RootCanvas->AddChildToCanvas(InventoryBox);
	InventorySlot->SetAnchors(FAnchors(0.03f, 0.92f));
	InventorySlot->SetAlignment(FVector2D(0.0f, 1.0f));
	InventorySlot->SetAutoSize(true);

	BuildInventorySlots(4);

	return Super::RebuildWidget();
}

void UOPMainHUDWidget::UpdateInventory(const TArray<FName>& ItemIds, int32 Capacity)
{
	if (!InventoryBox)
	{
		return;
	}

	if (InventorySlotTexts.Num() != Capacity)
	{
		BuildInventorySlots(Capacity);
	}

	for (int32 Index = 0; Index < InventorySlotTexts.Num(); ++Index)
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

void UOPMainHUDWidget::BuildInventorySlots(int32 SlotCount)
{
	if (!InventoryBox || !WidgetTree || SlotCount <= 0)
	{
		return;
	}

	InventoryBox->ClearChildren();
	InventorySlotTexts.Reset();

	for (int32 Index = 0; Index < SlotCount; ++Index)
	{
		UBorder* SlotBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		UTextBlock* SlotText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

		SlotText->SetText(FText::FromString(TEXT("- Empty -")));
		SlotBorder->SetPadding(FMargin(12.0f));
		SlotBorder->SetContent(SlotText);

		UHorizontalBoxSlot* HorizontalSlot = InventoryBox->AddChildToHorizontalBox(SlotBorder);
		HorizontalSlot->SetPadding(FMargin(4.0f, 0.0f, 4.0f, 0.0f));

		InventorySlotTexts.Add(SlotText);
	}
}