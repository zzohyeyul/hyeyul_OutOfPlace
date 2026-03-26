#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OPInteractionComponent.generated.h"

class AActor;
struct FInputActionValue;

UENUM()
enum class EOPInteractFailReason : uint8
{
	None,
	NoOwner,
	NoController,
	NoWorld,
	NoHit,
	NotInteractable,
	CannotInteract
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFocusChanged, AActor* /*OldFocus*/, AActor* /*NewFocus*/);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInteractResult, bool /*bSuccess*/, AActor* /*Target*/, EOPInteractFailReason /*Reason*/);

UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class HYEYUL_OUTOFPLACE_API UOPInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOPInteractionComponent();

	void OnInteractInput(const FInputActionValue& /*Value*/);

	bool Interact();
	AActor* GetCurrentFocusActor() const { return CurrentFocusActor.Get(); }

	FOnFocusChanged OnFocusChanged;
	FOnInteractResult OnInteractResult;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float TraceDistance = 300.f;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	bool bDrawDebug = true;

	TWeakObjectPtr<AActor> CurrentFocusActor;

	void PerformTrace();
};