#include "HUD/OPResultWidget.h"

#include "Components/TextBlock.h"

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