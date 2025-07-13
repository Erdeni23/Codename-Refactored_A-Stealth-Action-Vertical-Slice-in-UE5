// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Characters/PlayerCharacter.h"

//Native UE5 components
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

//Custom UE5 components
#include "Components/AdvancedMovementComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AdvancedMovementComponent = CreateDefaultSubobject<UAdvancedMovementComponent>(TEXT("AdvMoveComp"));;
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}



void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Enhanced Input 

void APlayerCharacter::Move(const FInputActionValue& MovementValue)
{
	MovementVector = MovementValue.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);

	ForwardVectorInputValue = MovementVector.Y; // - Прокси, не имеет отношения к Move
	
}


void APlayerCharacter::MouseLook(const FInputActionValue& MouseLookValue)
{
	MouseLookVector = MouseLookValue.Get<FVector2D>();
	AddControllerYawInput(MouseLookVector.X);
	AddControllerPitchInput(MouseLookVector.Y);
	
}


void APlayerCharacter::SprintBegin()
{
	if (GetCharacterMovement())
	{
		if (ForwardVectorInputValue == 0.9f) // если пытается бежать вдоль оси Forward Vector то
		{
			GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
		}
	}
}


void APlayerCharacter::SprintStop()
{
	if (GetCharacterMovement())
		GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	
}


void APlayerCharacter::CrouchSlide()
{
	if (AdvancedMovementComponent)
		AdvancedMovementComponent->CrouchSlideBegin();
	
}


void APlayerCharacter::UnCrouchSlide()
{
	if (AdvancedMovementComponent)
		AdvancedMovementComponent->CrouchSlideCompleted();
	
}


