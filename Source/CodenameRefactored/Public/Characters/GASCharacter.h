// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "GASCharacter.generated.h"


class UGameplayAbility;
class UGameplayEffect;
class UCustomAbilitySystemComponent;
class UCustomAttributeSet;
class ABaseWeapon;

UCLASS()
class CODENAMEREFACTORED_API AGASCharacter :
public ACharacter,
public IAbilitySystemInterface

{
	GENERATED_BODY()

public:
	
	AGASCharacter();
	
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	virtual void BeginPlay() override;
	
protected:
	//Functions

	//Variables
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABaseWeapon> CurrentlySwitchedWeapon;
	
	//Gameplay Ability System
public:
	
protected:
	//Functions
	void GiveDefaultAbilities();

	void InitDefaultAttributes() const;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual UCustomAttributeSet* GetAttributeSet() const;
	
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
