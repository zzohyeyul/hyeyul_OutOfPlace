#include "OPPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "Interaction/OPInteractionComponent.h"
#include "Items/OPInventoryComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AOPPlayerCharacter::AOPPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<UOPInteractionComponent>(TEXT("InteractionComp"));
	InventoryComp = CreateDefaultSubobject<UOPInventoryComponent>(TEXT("InventoryComp"));

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->MaxWalkSpeed = WalkSpeed;
	}
}

void AOPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->MaxWalkSpeed = WalkSpeed;
	}
}

void AOPPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EIC) return;

	if (IA_Move)  EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AOPPlayerCharacter::Move);
	if (IA_Look)  EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AOPPlayerCharacter::Look);

	if (IA_Run)
	{
		EIC->BindAction(IA_Run, ETriggerEvent::Started, this, &AOPPlayerCharacter::RunStarted);
		EIC->BindAction(IA_Run, ETriggerEvent::Completed, this, &AOPPlayerCharacter::RunCompleted);
	}

	if (IA_Interact && InteractionComp)
	{
		EIC->BindAction(IA_Interact, ETriggerEvent::Started, InteractionComp.Get(), &UOPInteractionComponent::OnInteractInput);
	}
}

void AOPPlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), Axis.Y);
		AddMovementInput(GetActorRightVector(), Axis.X);
	}
}

void AOPPlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(-Axis.Y);
}

void AOPPlayerCharacter::RunStarted(const FInputActionValue& Value)
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->MaxWalkSpeed = RunSpeed;
	}
}

void AOPPlayerCharacter::RunCompleted(const FInputActionValue& Value)
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->MaxWalkSpeed = WalkSpeed;
	}
}