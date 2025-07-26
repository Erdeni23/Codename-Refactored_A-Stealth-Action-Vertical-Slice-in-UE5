// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Characters/GASCharacter.h"
#include "Weapons/BaseWeapon.h"

//Gameplay Ability System
#include "AbilitySystem/CustomAttributeSet.h"
#include "AbilitySystem/CustomAbilitySystemComponent.h"



AGASCharacter::AGASCharacter()
{
	AttributeSet = CreateDefaultSubobject<UCustomAttributeSet>("AttributeSet");
	AbilitySystemComponent = CreateDefaultSubobject<UCustomAbilitySystemComponent>("AbilitySystemComponent");
}


void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!AbilitySystemComponent)
		UE_LOG(LogTemp, Error, TEXT("Ability System Component has a nullptr!"))
	if (!AttributeSet)
		UE_LOG(LogTemp, Error, TEXT("Attribute Set has a nullptr!"))
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	InitDefaultAttributes();
}


void AGASCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	
}


UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


UCustomAttributeSet* AGASCharacter::GetAttributeSet() const
{
	return AttributeSet;
}


void AGASCharacter::GiveDefaultAbilities()
{
	for (TSubclassOf<UGameplayAbility> Abilities : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(Abilities, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}


void AGASCharacter::InitDefaultAttributes() const
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


TObjectPtr<ABaseWeapon> AGASCharacter::GetCurrentlyEquippedWeapon()
{
	return CurrentlyEquippedWeapon;
}


FTransform AGASCharacter::GetShootTransform() const
{
	return ShootTransform;
}


