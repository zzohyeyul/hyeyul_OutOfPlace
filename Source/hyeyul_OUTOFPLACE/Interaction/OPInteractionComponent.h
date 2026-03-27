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
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionPromptChanged, const FText& /*PromptText*/);

UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class HYEYUL_OUTOFPLACE_API UOPInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOPInteractionComponent();

	void OnInteractInput(const FInputActionValue& /*Value*/);

	bool Interact();
	AActor* GetCurrentFocusActor() const { return CurrentFocusActor.Get(); }

	const FOnFocusChanged& GetOnFocusChanged() const { return OnFocusChanged; }
	FOnFocusChanged& GetOnFocusChanged() { return OnFocusChanged; }

	const FOnInteractResult& GetOnInteractResult() const { return OnInteractResult; }
	FOnInteractResult& GetOnInteractResult() { return OnInteractResult; }

	const FOnInteractionPromptChanged& GetOnInteractionPromptChanged() const { return OnInteractionPromptChanged; }
	FOnInteractionPromptChanged& GetOnInteractionPromptChanged() { return OnInteractionPromptChanged; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void PerformTrace();
	void BroadcastPrompt();
	FText BuildPromptText(AActor* FocusActor) const;

private:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float TraceDistance = 300.f;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	bool bDrawDebug = true;

	TWeakObjectPtr<AActor> CurrentFocusActor;
	FText CachedPromptText;

	FOnFocusChanged OnFocusChanged;
	FOnInteractResult OnInteractResult;
	FOnInteractionPromptChanged OnInteractionPromptChanged;
};