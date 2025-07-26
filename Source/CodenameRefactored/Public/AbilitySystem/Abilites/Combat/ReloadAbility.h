// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "ReloadAbility.generated.h"


class UGameplayEffect;
class ABaseWeapon;
class AGASCharacter;
class UAbilitySystemComponent;


UCLASS()
class CODENAMEREFACTORED_API UReloadAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UReloadAbility();

	virtual void ActivateAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
	) override;

	virtual bool CanActivateAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags = nullptr,
	const FGameplayTagContainer* TargetTags = nullptr,
	FGameplayTagContainer* OptionalRelevantTags = nullptr
	) const override;

	virtual void CancelAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility
	) override;

	virtual void EndAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled
	) override;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FireRateCooldown)
	TSubclassOf<UGameplayEffect> FireRateCooldownClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FireRateCooldown)
	float EffectLevel = 1.0f;

	
};
