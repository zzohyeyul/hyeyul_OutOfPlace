#pragma once

#include "CoreMinimal.h"
#include "Interaction/OPInteractableBase.h"
#include "OPExitDoor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UOPInventoryComponent;

UCLASS()
class HYEYUL_OUTOFPLACE_API AOPExitDoor : public AOPInteractableBase
{
	GENERATED_BODY()

public:
	AOPExitDoor();

	virtual bool CanInteract(AActor* Interactor) const override;
	virtual FText GetInteractText() const override;
	virtual void Interact(AActor* Interactor) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Exit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Exit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(VisibleAnywhere, Category = "Exit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Trigger;

	// 4개 수집이면 열리게
	UPROPERTY(EditAnywhere, Category = "Exit", meta = (ClampMin = "1"))
	int32 RequiredItemCount = 4;

	UPROPERTY(EditAnywhere, Category = "Exit")
	FText LockedText;

	UPROPERTY(EditAnywhere, Category = "Exit")
	FText ReadyText;

	UOPInventoryComponent* FindInventory(AActor* Interactor) const;
	bool HasEnoughItems(const UOPInventoryComponent* Inventory) const;
};