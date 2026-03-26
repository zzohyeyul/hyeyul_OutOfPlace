#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OPPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class HYEYUL_OUTOFPLACE_API AOPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
};