// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "GameCore/CustomPlayerController.h"

//UE5 Native
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h" 
#include "EnhancedInputComponent.h"

//Custom
#include "Characters/PlayerCharacter.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		Subsystem->AddMappingContext(MouseLookMappingContext, 1);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UEnhancedInputLocalPlayerSubsystem was not loaded"));
	}
	
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent was not loaded, check Plugins in Editor Preference"));
	}
	
}

void ACustomPlayerController::OnPossess(APawn* CurrentPawn)
{
	Super::OnPossess(CurrentPawn);

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (!PlayerCharacter)
		UE_LOG(LogTemp, Error, TEXT("Unable to get Player Character"));
		
	//BindAction (Что действует, Когда действует(на событие триггер или выполнено), Кто действует, Как действует)
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, PlayerCharacter, &APlayerCharacter::Move);
	EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, PlayerCharacter, &APlayerCharacter::MouseLook);
	EnhancedInputComponent->BindAction(CrouchSlideAction, ETriggerEvent::Ongoing, PlayerCharacter, &APlayerCharacter::CrouchSlide);
	EnhancedInputComponent->BindAction(CrouchSlideAction, ETriggerEvent::Completed, PlayerCharacter, &APlayerCharacter::UnCrouchSlide);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Ongoing, PlayerCharacter, &APlayerCharacter::SprintBegin);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, PlayerCharacter, &APlayerCharacter::SprintStop);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, PlayerCharacter, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, PlayerCharacter, &ACharacter::StopJumping);
}

