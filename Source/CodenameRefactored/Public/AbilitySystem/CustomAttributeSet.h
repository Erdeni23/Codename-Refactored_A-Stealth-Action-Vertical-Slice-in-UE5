// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"


#include "CustomAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
 

UCLASS()
class CODENAMEREFACTORED_API UCustomAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCustomAttributeSet();

	//Stats
	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCustomAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCustomAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UCustomAttributeSet, Stamina);
    	
    UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attr	ibute")
    FGameplayAttributeData MaxStamina;
    ATTRIBUTE_ACCESSORS(UCustomAttributeSet, MaxStamina);
protected:

	//Functions
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

private:
};
