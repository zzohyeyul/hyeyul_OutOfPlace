#include "HUD/OPResultWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Layout/Margin.h"

TSharedRef<SWidget> UOPResultWidget::RebuildWidget()
{
	WidgetTree = NewObject<UWidgetTree>(this, TEXT("ResultWidgetTree"));

	RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
	WidgetTree->RootWidget = RootCanvas;

	CenterBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("CenterBorder"));
	CenterBorder->SetPadding(FMargin(30.0f));

	ResultText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("ResultText"));
	ResultText->SetText(FText::GetEmpty());

	CenterBorder->SetContent(ResultText);

	UCanvasPanelSlot* CenterSlot = RootCanvas->AddChildToCanvas(CenterBorder);
	CenterSlot->SetAnchors(FAnchors(0.5f, 0.5f));
	CenterSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	CenterSlot->SetAutoSize(true);

	return Super::RebuildWidget();
}

void UOPResultWidget::SetGameResult(EOPGameResult InResult)
{
	if (!ResultText)
	{
		return;
	}

	switch (InResult)
	{
	case EOPGameResult::Cleared:
		ResultText->SetText(FText::FromString(TEXT("CLEAR")));
		break;

	case EOPGameResult::GameOver:
		ResultText->SetText(FText::FromString(TEXT("GAME OVER")));
		break;

	default:
		ResultText->SetText(FText::GetEmpty());
		break;
	}
}