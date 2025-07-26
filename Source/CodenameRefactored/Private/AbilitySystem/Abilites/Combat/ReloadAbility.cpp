// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "AbilitySystem/Abilites/Combat/ReloadAbility.h"
#include "GameplayEffect.h"
#include "Characters/GASCharacter.h"
#include "Weapons/BaseWeapon.h"
#include "AbilitySystemComponent.h"


UReloadAbility::UReloadAbility()
{
	
}

void UReloadAbility::ActivateAbility
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
	
	AGASCharacter* Character = Cast<AGASCharacter>(GetAvatarActorFromActorInfo());
	if (Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}
	
	ABaseWeapon* Weapon = Character->GetCurrentlyEquippedWeapon();
	if (Weapon)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}
	
	Weapon->ShootWeapon(Character->GetShootTransform());
	float FireCooldownDuration = 60.0f/Weapon->GetFireRate();
	TObjectPtr<UAbilitySystemComponent> ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	if (!FireRateCooldownClass)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}
	
	FGameplayEffectSpecHandle CooldownSpecHandle =
		ASC->MakeOutgoingSpec(FireRateCooldownClass, EffectLevel, ASC->MakeEffectContext());

	CooldownSpecHandle.Data->SetDuration(FireCooldownDuration,false);
	ASC->ApplyGameplayEffectSpecToSelf(*CooldownSpecHandle.Data.Get());

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}


bool UReloadAbility::CanActivateAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags
	) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	return true;
}


void UReloadAbility::CancelAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility
	)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}


void UReloadAbility::EndAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled
	)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
