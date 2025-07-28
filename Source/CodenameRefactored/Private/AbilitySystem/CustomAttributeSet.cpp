// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "AbilitySystem/CustomAttributeSet.h"
#include "GameplayEffectExtension.h"

UCustomAttributeSet::UCustomAttributeSet()
{
	
}


void UCustomAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
}


void UCustomAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) 
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
}