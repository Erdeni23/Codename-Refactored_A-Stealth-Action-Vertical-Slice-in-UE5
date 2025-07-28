// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "AbilitySystem/Abilites/Combat/ShootWeaponAbility.h"
#include "Characters/GASCharacter.h"
#include "Weapons/BaseWeapon.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h" // потому что потому


void UShootWeaponAbility::ActivateAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
	)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true); 
		return;
	}

	CommitAbility(Handle, ActorInfo, ActivationInfo);
	AGASCharacter* Character = Cast<AGASCharacter>(GetAvatarActorFromActorInfo());
	if (!Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	ABaseWeapon* Weapon = Character->GetCurrentlyEquippedWeapon();
	if (!Weapon)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	Weapon->ShootWeapon(Character->GetShootTransform());
	FireCooldownDuration = 60.0f/(Weapon->GetFireRate()); // Fire Rate - RPM
	
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}
	
	FGameplayEffectContextHandle ThisEffectContext = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle CooldownSpecHandle =
		ASC->MakeOutgoingSpec(FireRateCooldownClass, EffectLevel, ThisEffectContext);
	
	//используем блюпринт версию SetDuration потому что чёрная магия не позволяет сделать это напрямую и Эффект игнориует эту установку
	FGameplayEffectSpecHandle ModifiedSpecHandle = UAbilitySystemBlueprintLibrary::SetDuration(CooldownSpecHandle, FireCooldownDuration); 
	ASC->ApplyGameplayEffectSpecToSelf(*ModifiedSpecHandle.Data.Get());
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);

}