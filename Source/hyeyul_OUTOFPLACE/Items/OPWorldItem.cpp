#include "OPWorldItem.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/DataTable.h"

#include "Items/OPInventoryComponent.h"
#include "Items/OPItemTypes.h"

AOPWorldItem::AOPWorldItem()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);

	SetInteractText(FText::FromString(TEXT("Pick Up")));
}

UOPInventoryComponent* AOPWorldItem::FindInventory(AActor* Interactor) const
{
	return IsValid(Interactor) ? Interactor->FindComponentByClass<UOPInventoryComponent>() : nullptr;
}

bool AOPWorldItem::CanInteract(AActor* Interactor) const
{
	if (!GetCanInteractFlag()) return false;
	if (ItemId.IsNone()) return false;

	UOPInventoryComponent* Inv = FindInventory(Interactor);
	if (!Inv) return false;

	if (Inv->HasItemId(ItemId)) return false;
	if (Inv->GetCount() >= Inv->GetCapacity()) return false;

	return true;
}

FText AOPWorldItem::GetItemDisplayNameFromTable() const
{
	if (!ItemDataTable || ItemId.IsNone())
	{
		return FText::GetEmpty();
	}

	const FOPItemRow* Row = ItemDataTable->FindRow<FOPItemRow>(ItemId, TEXT("GetItemName"));
	return Row ? Row->DisplayName : FText::GetEmpty();
}

FText AOPWorldItem::GetInteractText() const
{
	const FText Name = GetItemDisplayNameFromTable();
	if (!Name.IsEmpty())
	{
		return FText::Format(FText::FromString(TEXT("Pick Up : {0}")), Name);
	}
	return GetInteractTextRef();
}

void AOPWorldItem::Interact(AActor* Interactor)
{
	UOPInventoryComponent* Inv = FindInventory(Interactor);
	if (!Inv) return;

	if (Inv->AddItemId(ItemId))
	{
		Destroy();
	}
}