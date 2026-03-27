#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/OPGameModeBase.h"
#include "OPResultWidget.generated.h"

class UCanvasPanel;
class UBorder;
class UTextBlock;

UCLASS()
class HYEYUL_OUTOFPLACE_API UOPResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	void SetGameResult(EOPGameResult InResult);

private:
	UPROPERTY()
	TObjectPtr<UCanvasPanel> RootCanvas = nullptr;

	UPROPERTY()
	TObjectPtr<UBorder> CenterBorder = nullptr;

	UPROPERTY()
	TObjectPtr<UTextBlock> ResultText = nullptr;
};