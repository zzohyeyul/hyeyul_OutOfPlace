#include "OPInventoryComponent.h"

UOPInventoryComponent::UOPInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UOPInventoryComponent::AddItemId(const FName& ItemId)
{
	if (ItemId.IsNone())
	{
		return false;
	}

	if (ItemIds.Num() >= Capacity)
	{
		return false;
	}

	// 중복 4개 수집 컨셉이라 비허용
	if (ItemIds.Contains(ItemId))
	{
		return false;
	}

	ItemIds.Add(ItemId);
	OnInventoryChanged.Broadcast();
	return true;
}

bool UOPInventoryComponent::HasItemId(const FName& ItemId) const
{
	return ItemIds.Contains(ItemId);
}