#include "Interaction/OPInteractableBase.h"

AOPInteractableBase::AOPInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;
	InteractText = FText::FromString(TEXT("Interact"));
}

bool AOPInteractableBase::CanInteract(AActor* Interactor) const
{
	return bCanInteract;
}

FText AOPInteractableBase::GetInteractText(AActor* Interactor) const
{
	return InteractText;
}

void AOPInteractableBase::Interact(AActor* Interactor)
{
}