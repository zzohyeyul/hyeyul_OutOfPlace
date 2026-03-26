#include "OPInteractableBase.h"

AOPInteractableBase::AOPInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;
	InteractText = FText::FromString(TEXT("Interact"));
}

bool AOPInteractableBase::CanInteract(AActor* Interactor) const
{
	return bCanInteract;
}

FText AOPInteractableBase::GetInteractText() const
{
	return InteractText;
}

void AOPInteractableBase::Interact(AActor* Interactor)
{
	// 기본 동작 없음 - 상속 클래스에서 override
}