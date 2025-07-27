// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "ReloadAbility.generated.h"


class UGameplayEffect;
class ABaseWeapon;
class AGASCharacter;
class UAbilitySystemComponent;


UCLASS(Blueprintable)
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


protected:
	UFUNCTION()
	void OnMontageCompleted();

	UFUNCTION()
	void OnMontageInterrupted();

	UPROPERTY()
	TObjectPtr<ABaseWeapon> CurrentWeapon;

	UPROPERTY()
	TObjectPtr<AGASCharacter> Character;

	FActiveGameplayEffectHandle MontageTaskHandle;
	
};
