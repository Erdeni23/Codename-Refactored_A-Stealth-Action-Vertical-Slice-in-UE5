// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
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

	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCustomAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCustomAttributeSet, MaxHealth);

};
