#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/ObjectPtr.h"
#include "OPPlayerCharacter.generated.h"

class UInputAction;
class UOPInteractionComponent;
class UOPInventoryComponent;

UCLASS()
class HYEYUL_OUTOFPLACE_API AOPPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOPPlayerCharacter();

	UOPInteractionComponent* GetInteractionComponent() const { return InteractionComp; }
	UOPInventoryComponent* GetInventoryComponent() const { return InventoryComp; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void RunStarted(const struct FInputActionValue& Value);
	void RunCompleted(const struct FInputActionValue& Value);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Run;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Interact;

	UPROPERTY(EditAnywhere, Category = "Move")
	float WalkSpeed = 350.f;

	UPROPERTY(EditAnywhere, Category = "Move")
	float RunSpeed = 600.f;

	UPROPERTY(VisibleAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UOPInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UOPInventoryComponent> InventoryComp;
};