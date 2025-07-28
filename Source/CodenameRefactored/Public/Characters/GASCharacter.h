// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/InteractInterface.h"

#include "GASCharacter.generated.h"


class UGameplayAbility;
class UGameplayEffect;
class UCustomAbilitySystemComponent;
class UCustomAttributeSet;
class ABaseWeapon;

UCLASS()
class CODENAMEREFACTORED_API AGASCharacter :
public ACharacter,
public IAbilitySystemInterface,
public IInteractInterface

{
	GENERATED_BODY()

public:
	
	AGASCharacter();
	
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	virtual void BeginPlay() override;

	TObjectPtr<ABaseWeapon> GetCurrentlyEquippedWeapon();

	FTransform GetShootTransform() const;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual UCustomAttributeSet* GetAttributeSet() const;

protected:
	//Variables
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABaseWeapon> CurrentlyEquippedWeapon;

	//Functions
	UPROPERTY(BlueprintReadWrite)
	FTransform ShootTransform;
	
	
	//Gameplay Ability System
public:
	
protected:
	//Functions
	void GiveDefaultAbilities();

	void InitDefaultAttributes() const;

	//Defaults
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;  // Статы

	//Components
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCustomAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UCustomAttributeSet> AttributeSet;
private:

};
