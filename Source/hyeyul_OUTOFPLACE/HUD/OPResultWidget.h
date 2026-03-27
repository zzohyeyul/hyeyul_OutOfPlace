#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/OPGameModeBase.h"
#include "OPResultWidget.generated.h"

class UTextBlock;

UCLASS()
class HYEYUL_OUTOFPLACE_API UOPResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetGameResult(EOPGameResult InResult);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText = nullptr;
};