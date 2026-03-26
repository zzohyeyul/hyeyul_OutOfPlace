#include "OPInteractionComponent.h"

#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "InputActionValue.h"

#include "Interaction/OPInteractableBase.h"

UOPInteractionComponent::UOPInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOPInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UOPInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformTrace();
}

void UOPInteractionComponent::OnInteractInput(const FInputActionValue& /*Value*/)
{
	Interact();
}

void UOPInteractionComponent::PerformTrace()
{
	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();
	APawn* PawnOwner = Cast<APawn>(Owner);
	APlayerController* PC = PawnOwner ? Cast<APlayerController>(PawnOwner->GetController()) : nullptr;
	APlayerCameraManager* Cam = PC ? PC->PlayerCameraManager : nullptr;

	if (!World || !Owner || !PawnOwner || !PC || !Cam)
	{
		return;
	}

	const FVector Start = Cam->GetCameraLocation();
	const FVector End = Start + (Cam->GetActorForwardVector() * TraceDistance);

	FHitResult Hit;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(OP_InteractTrace), false);
	Params.AddIgnoredActor(Owner);

	const bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	if (bDrawDebug)
	{
		DrawDebugLine(World, Start, End, bHit ? FColor::Green : FColor::Red, false, 0.f, 0, 1.f);
	}

	AActor* NewFocus = bHit ? Hit.GetActor() : nullptr;
	AActor* OldFocus = CurrentFocusActor.Get();

	if (OldFocus != NewFocus)
	{
		CurrentFocusActor = NewFocus;
		OnFocusChanged.Broadcast(OldFocus, NewFocus);
	}
}

bool UOPInteractionComponent::Interact()
{
	AActor* Owner = GetOwner();
	UWorld* World = GetWorld();
	APawn* PawnOwner = Cast<APawn>(Owner);
	AController* Controller = PawnOwner ? PawnOwner->GetController() : nullptr;

	if (!Owner || !World)
	{
		OnInteractResult.Broadcast(false, nullptr, !Owner ? EOPInteractFailReason::NoOwner : EOPInteractFailReason::NoWorld);
		return false;
	}

	if (!PawnOwner || !Controller)
	{
		OnInteractResult.Broadcast(false, nullptr, EOPInteractFailReason::NoController);
		return false;
	}

	AActor* Target = CurrentFocusActor.Get();
	if (!Target)
	{
		OnInteractResult.Broadcast(false, nullptr, EOPInteractFailReason::NoHit);
		return false;
	}

	AOPInteractableBase* Interactable = Cast<AOPInteractableBase>(Target);
	if (!Interactable)
	{
		OnInteractResult.Broadcast(false, Target, EOPInteractFailReason::NotInteractable);
		return false;
	}

	if (!Interactable->CanInteract(Owner))
	{
		OnInteractResult.Broadcast(false, Target, EOPInteractFailReason::CannotInteract);
		return false;
	}

	// 실행
	Interactable->Interact(Owner);

	OnInteractResult.Broadcast(true, Target, EOPInteractFailReason::None);
	return true;
}