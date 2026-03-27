#include "Actor/OPExitDoor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Items/OPInventoryComponent.h"
#include "Framework/OPGameModeBase.h"

AOPExitDoor::AOPExitDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(Root);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Root);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	LockedText = FText::FromString(TEXT("Need 4 items"));
	ReadyText = FText::FromString(TEXT("Exit"));

	SetInteractText(ReadyText);
}

UOPInventoryComponent* AOPExitDoor::FindInventory(AActor* Interactor) const
{
	return IsValid(Interactor) ? Interactor->FindComponentByClass<UOPInventoryComponent>() : nullptr;
}

bool AOPExitDoor::HasEnoughItems(const UOPInventoryComponent* Inventory) const
{
	if (!Inventory)
	{
		return false;
	}

	return Inventory->GetCount() >= RequiredItemCount;
}

bool AOPExitDoor::CanInteract(AActor* Interactor) const
{
	if (!GetCanInteractFlag())
	{
		return false;
	}

	UOPInventoryComponent* Inv = FindInventory(Interactor);
	if (!Inv)
	{
		return false;
	}

	return HasEnoughItems(Inv);
}

FText AOPExitDoor::GetInteractText(AActor* Interactor) const
{
	UOPInventoryComponent* Inv = FindInventory(Interactor);
	if (!Inv)
	{
		return LockedText;
	}

	return HasEnoughItems(Inv) ? ReadyText : LockedText;
}

void AOPExitDoor::Interact(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AOPGameModeBase* GM = Cast<AOPGameModeBase>(World->GetAuthGameMode());
	if (!GM)
	{
		return;
	}

	GM->RequestGameClear(Interactor);
}