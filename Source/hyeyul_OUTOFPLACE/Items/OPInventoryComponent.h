#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OPInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class HYEYUL_OUTOFPLACE_API UOPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOPInventoryComponent();

	bool AddItemId(const FName& ItemId);
	bool HasItemId(const FName& ItemId) const;

	int32 GetCapacity() const { return Capacity; }
	int32 GetCount() const { return ItemIds.Num(); }
	const TArray<FName>& GetItemIds() const { return ItemIds; }

	const FOnInventoryChanged& GetOnInventoryChanged() const { return OnInventoryChanged; }
	FOnInventoryChanged& GetOnInventoryChanged() { return OnInventoryChanged; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Capacity = 4;

	UPROPERTY()
	TArray<FName> ItemIds;

	FOnInventoryChanged OnInventoryChanged;
};