// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Characters/PlayerCharacter.h"

//Native UE5 components
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameplayEffect.h"

//Custom UE5 components
#include "Components/AdvancedMovementComponent.h"
#include "AbilitySystem/CustomAbilitySystemComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AdvancedMovementComponent = CreateDefaultSubobject<UAdvancedMovementComponent>(TEXT("AdvMoveComp"));
	AttributeSet = CreateDefaultSubobject<UCustomAttributeSet>("AttributeSet");
	AbilitySystemComponent = CreateDefaultSubobject<UCustomAbilitySystemComponent>("AbilitySystemComponent");
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!AbilitySystemComponent)
		UE_LOG(LogTemp, Error, TEXT("Ability System Component has a nullptr!"))
	if (!GetCharacterMovement())
		UE_LOG(LogTemp, Error, TEXT("Character Movement component has a nullptr!"))
	if (AdvancedMovementComponent)
		UE_LOG(LogTemp, Error, TEXT("Advanced Movement Component has a nullptr!"))

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	InitDefaultAttributes();

	//Привязываем изменение хп к событию, для использования в HUD/Blueprint
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &APlayerCharacter::HandleHealthChanged);
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


//Gameplay Ability System
UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


UCustomAttributeSet* APlayerCharacter::GetAttributeSet() const
{
	return AttributeSet;
}


void APlayerCharacter::GiveDefaultAbilities()
{
	for (TSubclassOf<UGameplayAbility> Abilities : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(Abilities, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}


void APlayerCharacter::InitDefaultAttributes() const
{
	if (!AbilitySystemComponent || !DefaultAttributeEffect)
		return;
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec
		(
		DefaultAttributeEffect,
		1.0f,
		EffectContext
		);

	if (SpecHandle.IsValid())
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void APlayerCharacter::HandleHealthChanged(const FOnAttributeChangeData& Data)
{
	float NewHealth = Data.NewValue;
	float OldHealth = Data.OldValue;

	float DeltaValue = NewHealth - OldHealth;

	OnHealthChanged(DeltaValue, FGameplayTagContainer());
}
