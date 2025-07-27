// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "AbilitySystem/Abilites/Combat/ReloadAbility.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Characters/GASCharacter.h"
#include "Weapons/BaseWeapon.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

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
	CommitAbility(Handle, ActorInfo, ActivationInfo);
	UE_LOG(LogTemp, Log, TEXT("ReloadAbility: CommitAbility succeeded."));
	
	Character = Cast<AGASCharacter>(GetAvatarActorFromActorInfo());
	if (!Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true); 
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("ReloadAbility: Character succeeded."));
	
	CurrentWeapon = Character->GetCurrentlyEquippedWeapon();
	if (!CurrentWeapon->CanReload())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true); 
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("ReloadAbility: Weapon succeeded."));
	
	TObjectPtr<UAnimMontage> ReloadMontage = CurrentWeapon->GetReloadMontage();
	if (!ReloadMontage)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true); 
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("ReloadAbility: ReloadMontage succeeded."));
	
	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ReloadMontage, 1.0f);
	if (MontageTask)
	{
		MontageTask->OnCompleted.AddDynamic(this, &UReloadAbility::OnMontageCompleted);
		MontageTask->OnInterrupted.AddDynamic(this, &UReloadAbility::OnMontageInterrupted);
		MontageTask->ReadyForActivation();
	}
	

}


void UReloadAbility::OnMontageCompleted()
{
	if (CurrentWeapon)
		CurrentWeapon->FinishReload();
	CurrentWeapon = nullptr;
	bool bWasCancelled = false;
	UE_LOG(LogTemp, Log, TEXT("OnMontageCompleted"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}


void UReloadAbility::OnMontageInterrupted()
{
	CurrentWeapon = nullptr;
	bool bWasCancelled = true;
	UE_LOG(LogTemp, Log, TEXT("OnMontageInterrupted"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}





