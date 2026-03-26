#include "OPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AOPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LP = GetLocalPlayer();
	if (!LP) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem) return;

	if (!DefaultMappingContext) return;

	Subsystem->AddMappingContext(DefaultMappingContext, 0);
}