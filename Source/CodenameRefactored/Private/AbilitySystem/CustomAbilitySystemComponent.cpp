// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "AbilitySystem/CustomAbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

UCustomAbilitySystemComponent::UCustomAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCustomAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCustomAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

