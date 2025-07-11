// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Characters/PlayerCharacter.h"

//components

#include "Camera/PlayerCameraManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"



APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

	PlayerCameraManager->ViewPitchMax = defaultCameraViewPitchMax;
	PlayerCameraManager->ViewPitchMin = defaultCameraViewPitchMin;
	PlayerCameraManager->ViewYawMax = defaultCameraViewYawMax;
	PlayerCameraManager->ViewYawMin = defaultCameraViewYawMin;
	
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//CrouchSlide begin

void APlayerCharacter::DoCrouch()
{
	Crouch();
	GetCapsuleComponent()->SetCapsuleRadius(60.0f);
		
	float DelayDuration = UGameplayStatics::GetGlobalTimeDilation(this);

	GetWorld()->GetTimerManager().SetTimer(
	Delay,							
	this,								
	&APlayerCharacter::CrouchSlideCompleted,			
	DelayDuration,                    
	false									
	);
}

void APlayerCharacter::SlideCrouch()
{
	if (!GetCharacterMovement()->IsFalling() &&
		(!bIsSliding && (GetCharacterMovement()->Velocity.Size2D()>800)))
	{
		bIsSliding = true;
		bUseControllerRotationYaw = false;
		
		PlayerCameraManager->ViewYawMax = PlayerCameraManager->GetCameraRotation().Yaw + 90;
		PlayerCameraManager->ViewYawMin = PlayerCameraManager->GetCameraRotation().Yaw - 30;
		PlayerCameraManager->ViewPitchMin = -40;

		DoCrouch();
	}
	
	else if (!GetCharacterMovement()->IsFalling() &&
		(!bIsSliding && (GetCharacterMovement()->Velocity.Size2D()<800)))
	{
		DoCrouch();
	}
	
	else
		return;
	
}

void APlayerCharacter::CrouchSlideCompleted()
{
	GetWorld()->GetTimerManager().ClearTimer(Delay);
	bIsSliding = false;
	bUseControllerRotationYaw = true;
	
	PlayerCameraManager->ViewYawMax = defaultCameraViewYawMax;
	PlayerCameraManager->ViewYawMin = defaultCameraViewYawMin;
	PlayerCameraManager->ViewPitchMin = defaultCameraViewPitchMin;
	
}

//CrouchSlide end


