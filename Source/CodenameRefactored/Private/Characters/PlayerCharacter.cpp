// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Characters/PlayerCharacter.h"

//Native UE5 components
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameplayEffect.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

//Custom UE5 components
#include "Components/AdvancedMovementComponent.h"
#include "AbilitySystem/CustomAttributeSet.h"
#include "AbilitySystem/CustomAbilitySystemComponent.h"
#include "Weapons/BaseWeapon.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AdvancedMovementComponent = CreateDefaultSubobject<UAdvancedMovementComponent>(TEXT("AdvMoveComp"));

}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

	
	if (!GetCharacterMovement())
		UE_LOG(LogTemp, Error, TEXT("Character Movement component has a nullptr!"))
	if (!AdvancedMovementComponent)
		UE_LOG(LogTemp, Error, TEXT("Advanced Movement Component has a nullptr!"))
	
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
	if (ForwardVectorInputValue >= 0.9f) // если пытается бежать вдоль оси Forward Vector то
		GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
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


TArray<UPrimitiveComponent*> APlayerCharacter::GetComponentsToIgnoreForCollision_Implementation() const
{
	TArray<UPrimitiveComponent*> ComponentsToIgnore;

	if (GetCapsuleComponent())
		ComponentsToIgnore.Add(GetCapsuleComponent());
	
	if (GetMesh())
		ComponentsToIgnore.Add(GetMesh());
	
	return ComponentsToIgnore;
}


AActor* APlayerCharacter::InteractWithObject()
{
	FVector TraceStart = PlayerCameraManager->GetRootComponent()->GetComponentLocation();
	
	FVector TraceEnd = TraceStart + InteractionDistance* PlayerCameraManager->GetRootComponent()->GetForwardVector();
	
	FCollisionShape TraceShape = FCollisionShape::MakeSphere(InteractionSphereRadius);

	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")));
	TraceParams.bTraceComplex = false; 
	TraceParams.bReturnPhysicalMaterial = false; 
	TraceParams.AddIgnoredActor(this);

	ECollisionChannel TraceChannel = ECC_Visibility; 
	
	FHitResult OutHit(ForceInit); // для сферического трейса обязательно проинициализировать

	bool bHit = GetWorld()->SweepSingleByChannel(
		OUT OutHit,
		TraceStart,
		TraceEnd,
		FQuat::Identity, //структура нулевого вращения
		TraceChannel,
		TraceShape,
		TraceParams
	);
	
	//УДАЛИТЬ ПОСЛЕ ДЕБАГА BEGIN
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, bHit ? FColor::Green : FColor::Green, false, 1.0f, 0, 2.0f);
	DrawDebugSphere(GetWorld(), TraceStart, InteractionSphereRadius, 12, FColor::Green, false, 1.0f);
	DrawDebugSphere(GetWorld(), TraceEnd, InteractionSphereRadius, 12, FColor::Green, false, 1.0f);
	//УДАЛИТЬ ПОСЛЕ ДЕБАГА END

	AActor* HitActor = nullptr;
	if (bHit)
		HitActor = OutHit.GetActor();
	
	if (HitActor)
	{
		IInteractInterface* InteractableActor = Cast<IInteractInterface>(HitActor);
		
		bool bEquip = false;
		if (!CurrentlyEquippedWeapon)
			bEquip = true;
		
		if (InteractableActor)
			InteractableActor->Execute_Interact(HitActor, GetMesh(), bEquip);

		if (bEquip)
			CurrentlyEquippedWeapon = Cast<ABaseWeapon>(HitActor);
	}
	
	return HitActor;
}


//Gameplay Ability System



