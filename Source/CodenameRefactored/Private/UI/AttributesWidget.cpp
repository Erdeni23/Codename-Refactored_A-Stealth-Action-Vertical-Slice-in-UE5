// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "UI/AttributesWidget.h"
#include "AbilitySystem/CustomAttributeSet.h"
#include "Characters/GASCharacter.h"

void UAttributesWidget::BindToAttributes()
{
	APawn* Character = GetOwningPlayerPawn();

	UAbilitySystemComponent* ASC = Cast<AGASCharacter>(Character)->GetAbilitySystemComponent();
	UCustomAttributeSet* AttributeSet = Cast<AGASCharacter>(Character)->GetAttributeSet();

	HealthPercent =
		(AttributeSet->GetHealthAttribute().GetNumericValue(AttributeSet)) /
		(AttributeSet->GetMaxHealthAttribute().GetNumericValue(AttributeSet));

	StaminaPercent =
		(AttributeSet->GetStaminaAttribute().GetNumericValue(AttributeSet)) /
		(AttributeSet->GetMaxStaminaAttribute().GetNumericValue(AttributeSet));

	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddLambda
	(
		[this, AttributeSet](const FOnAttributeChangeData& Data)
		{
			HealthPercent = Data.NewValue / (AttributeSet->GetMaxHealthAttribute().GetNumericValue(AttributeSet));
		}
	);

	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddLambda
	(
		[this, AttributeSet](const FOnAttributeChangeData& Data)
		{
			HealthPercent = Data.NewValue / (AttributeSet->GetMaxStaminaAttribute().GetNumericValue(AttributeSet));
		}
	);
}
