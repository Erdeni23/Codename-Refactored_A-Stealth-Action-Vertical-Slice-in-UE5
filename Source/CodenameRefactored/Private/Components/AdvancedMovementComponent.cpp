// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Components/AdvancedMovementComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


UAdvancedMovementComponent::UAdvancedMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UAdvancedMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	 * получаем информацию о владельце:
	 * Референс на владельца типа ACharacter
	 * Референс на контроллер владельца типа APlayerController
	 * Референс на компонент передвижения типа UCharacterMovementComponent
	 * Референс на компонент капсулы типа UCapsuleComponent
	 * Референс на менеджера камеры типа APlayerCameraManager
	*/
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT(
			"AdvancedMovementComponent can be used only on ACharacter! Component on Object '%s' will be deactivated"),
			*GetOwner()->GetName());
		Deactivate(); 
		return;       
	}
	
	OwnerPlayerController = Cast<APlayerController>(OwnerCharacter->GetController());
	if (OwnerPlayerController)
	{
		OwnerPlayerIndex = UGameplayStatics::GetPlayerControllerID(OwnerPlayerController);
		UE_LOG(LogTemp, Warning, TEXT("Object '%s' Player Index: %d"),*GetOwner()->GetName(), OwnerPlayerIndex);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Object '%s' has a nullptr as a PlayerController"), *GetOwner()->GetName());
	}

	OwnerMovementComponent = Cast<UCharacterMovementComponent>(OwnerCharacter->GetMovementComponent());
	if (!OwnerMovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Object '%s' has a nullptr as a MovementComponent"), *GetOwner()->GetName());
	}

	OwnerCapsuleComponent = Cast<UCapsuleComponent>(OwnerCharacter->GetCapsuleComponent());
	if (!OwnerCapsuleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Object '%s' has a nullptr as a CapsuleComponent"), *GetOwner()->GetName());
	}
	
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, OwnerPlayerIndex);
	if (!PlayerCameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Object '%s' has a nullptr as a PlayerCameraManager"), *GetOwner()->GetName());
	}

	// ограничиваем угол обзора
	PlayerCameraManager->ViewPitchMax = DefaultCameraViewPitchMax;
	PlayerCameraManager->ViewPitchMin = DefaultCameraViewPitchMin;
	PlayerCameraManager->ViewYawMax = DefaultCameraViewYawMax;
	PlayerCameraManager->ViewYawMin = DefaultCameraViewYawMin;
	
}

void UAdvancedMovementComponent::DoCrouch()
{
	OwnerCharacter->Crouch();
	OwnerCapsuleComponent->SetCapsuleRadius(CrouchedCapsuleRadius);
		
	float DelayDuration = UGameplayStatics::GetGlobalTimeDilation(this);

	GetWorld()->GetTimerManager().SetTimer(
	Delay,							
	this,								
	&UAdvancedMovementComponent::CrouchSlideCompleted,			
	DelayDuration,                    
	false									
	);
	
}

void UAdvancedMovementComponent::CrouchSlideBegin()
{
	if (!OwnerMovementComponent || !OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("CrouchSlideBegin called on an uninitialized component!"));
		return;
	}
	
	if (OwnerMovementComponent->IsFalling() && bIsSliding)
	{
		return;
	}
	
	if(OwnerMovementComponent->Velocity.Size2D()>MinSpeedForSlide)
	{
		bIsSliding = true;
		OwnerCharacter->bUseControllerRotationYaw = false;
		
		PlayerCameraManager->ViewYawMax = PlayerCameraManager->GetCameraRotation().Yaw + 90;
		PlayerCameraManager->ViewYawMin = PlayerCameraManager->GetCameraRotation().Yaw - 30;
		PlayerCameraManager->ViewPitchMin = -40;
	}
	
	DoCrouch();
	
}

void UAdvancedMovementComponent::SlideCompleted()
{
	if (!OwnerMovementComponent || !OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("SlideCompleted called on an uninitialized component!"));
		return;
	}
	
	GetWorld()->GetTimerManager().ClearTimer(Delay);
	bIsSliding = false;
	OwnerCharacter->bUseControllerRotationYaw = true;
	
	PlayerCameraManager->ViewYawMax = DefaultCameraViewYawMax;
	PlayerCameraManager->ViewYawMin = DefaultCameraViewYawMin;
	PlayerCameraManager->ViewPitchMin = DefaultCameraViewPitchMin;
	
}

void UAdvancedMovementComponent::CrouchSlideCompleted()
{
	OwnerCharacter->UnCrouch();
	SlideCompleted();
}

void UAdvancedMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

