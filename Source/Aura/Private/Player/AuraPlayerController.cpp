// Copyright Druid Mechanics


#include "Player/AuraPlayerController.h"

//UEnhancedInputLocalPlayerSubsystem in EnhancedInputSubsystems.h
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//Set Argument Value
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	//Get Current Rotation Value
	const FRotator Rotator = GetControlRotation();

	//Sey Current Yaw Rotation
	const FRotator YawRotation(0.f,Rotator.Yaw,0.f);

	//Create ForwardDirection From YawRotation
	//GetUnitAxis return normalized vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//Not Using CheckFunction because This Function call Tick  
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		//Input Value Setting to  Movement Input of Character
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
}
