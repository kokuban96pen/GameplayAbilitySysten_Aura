// Copyright Druid Mechanics


#include "Player/AuraPlayerController.h"

//UEnhancedInputLocalPlayerSubsystem in EnhancedInputSubsystems.h
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	//Subsystem is Singleton
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem)
	Subsystem->AddMappingContext(AuraContext, 0);

	//show MouseCursor Flag
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//MouseCursor Settings
	FInputModeGameAndUI InputModeData;
	//Not Lock on viewport
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//Not hide on viewport
	InputModeData.SetHideCursorDuringCapture(false);

	//Set InputModeData to InputMode of PlayerController
	SetInputMode(InputModeData);
}
