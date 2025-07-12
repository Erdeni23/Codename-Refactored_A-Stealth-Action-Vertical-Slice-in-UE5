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
	
	if (!IsValid(AdvancedMovementComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AdvancedMovementComponent has a nullptr"));
	}

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
	if (ForwardVectorInputValue == 1.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
	}
	
}


void APlayerCharacter::SprintStop()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	
}


void APlayerCharacter::CrouchSlide()
{
	AdvancedMovementComponent->CrouchSlideBegin();
	
}


void APlayerCharacter::UnCrouchSlide()
{
	AdvancedMovementComponent->CrouchSlideCompleted();
	
}


