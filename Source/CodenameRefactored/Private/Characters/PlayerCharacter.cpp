// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Characters/PlayerCharacter.h"

//Native UE5 components
#include "Kismet/GameplayStatics.h"

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
	
	if (IsValid(AdvancedMovementComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AdvancedMovementComponent has a nullptr"));
	}
	else
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

void APlayerCharacter::SlideCrouch()
{
	AdvancedMovementComponent->CrouchSlideBegin();
}

void APlayerCharacter::UnSlideCrouch()
{
	AdvancedMovementComponent->CrouchSlideCompleted();
}


