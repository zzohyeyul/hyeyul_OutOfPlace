#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OPInteractableBase.generated.h"

UCLASS(Abstract)
class HYEYUL_OUTOFPLACE_API AOPInteractableBase : public AActor
{
	GENERATED_BODY()

public:
	AOPInteractableBase();

	virtual bool CanInteract(AActor* Interactor) const;
	virtual FText GetInteractText(AActor* Interactor) const;
	virtual void Interact(AActor* Interactor);

protected:
	bool GetCanInteractFlag() const { return bCanInteract; }
	void SetCanInteractFlag(bool bNewCanInteract) { bCanInteract = bNewCanInteract; }

	const FText& GetInteractTextRef() const { return InteractText; }
	void SetInteractText(const FText& NewText) { InteractText = NewText; }

private:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	bool bCanInteract = true;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	FText InteractText;
};