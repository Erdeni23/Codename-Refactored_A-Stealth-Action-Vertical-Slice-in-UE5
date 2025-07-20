// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Components/HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UHealthComponent::TakeDamage(float Damage)
{
	CurrentHealth -= Damage;
	
	OnDamageTaken.Broadcast();
	
	if (CurrentHealth<=0)
		OnDeath.Broadcast();
	
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

