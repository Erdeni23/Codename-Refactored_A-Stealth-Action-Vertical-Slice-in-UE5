// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ShootWeaponAbility.generated.h"


class UGameplayEffect;
class ABaseWeapon;
class AGASCharacter;
class UAbilitySystemComponent;

UCLASS()
class CODENAMEREFACTORED_API UShootWeaponAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	virtual void ActivateAbility
	(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
	) override;


protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FireRateCooldown)
	TSubclassOf<UGameplayEffect> FireRateCooldownClass;
	
	float FireCooldownDuration;
	float EffectLevel = 1.0f;

	
};
