#pragma once

#include "CoreMinimal.h"
#include "Interaction/OPInteractableBase.h"
#include "OPWorldItem.generated.h"

class UStaticMeshComponent;
class UDataTable;
class UOPInventoryComponent;

UCLASS()
class HYEYUL_OUTOFPLACE_API AOPWorldItem : public AOPInteractableBase
{
	GENERATED_BODY()

public:
	AOPWorldItem();

	virtual bool CanInteract(AActor* Interactor) const override;
	virtual FText GetInteractText(AActor* Interactor) const override;
	virtual void Interact(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	FName ItemId;

	UPROPERTY(EditAnywhere, Category = "Item")
	TObjectPtr<UDataTable> ItemDataTable;

	UOPInventoryComponent* FindInventory(AActor* Interactor) const;
	FText GetItemDisplayNameFromTable() const;
};