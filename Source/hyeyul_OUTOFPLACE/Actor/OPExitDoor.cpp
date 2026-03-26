#include "OPExitDoor.h"

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

	// AOPInteractableBase 에서 상속 (캡슐화/방어코드)
	// 상태별 텍스트는 GetInteractText에서 반환
	SetInteractText(ReadyText);
}

UOPInventoryComponent* AOPExitDoor::FindInventory(AActor* Interactor) const
{
	return IsValid(Interactor) ? Interactor->FindComponentByClass<UOPInventoryComponent>() : nullptr;
}

bool AOPExitDoor::HasEnoughItems(const UOPInventoryComponent* Inventory) const
{
	if (!Inventory) return false;
	return Inventory->GetCount() >= RequiredItemCount;
}

bool AOPExitDoor::CanInteract(AActor* Interactor) const
{
	if (!GetCanInteractFlag()) return false;

	UOPInventoryComponent* Inv = FindInventory(Interactor);
	if (!Inv) return false;

	if (!HasEnoughItems(Inv)) return false;

	return true;
}

FText AOPExitDoor::GetInteractText() const
{
	// InteractionComponent 가 포커스된 대상에서 이 함수를 호출하는 구조니까 여기서는 Interactor 를 못 받음
	// 그래서 텍스트는 기본 Ready/Locked 만 제공하고 정확한 상태표시는 HUD에서 만들기
	return LockedText;
	// 기본은 잠김 텍스트 (실제 성공 여부는 Interact에서 CanInteract로)
}

void AOPExitDoor::Interact(AActor* Interactor)
{
	if (!CanInteract(Interactor)) return;

	UWorld* World = GetWorld();
	if (!World) return;

	AOPGameModeBase* GM = Cast<AOPGameModeBase>(World->GetAuthGameMode());
	if (!GM) return;

	GM->RequestGameClear(Interactor);
}