// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Subsystems/ActorPoolGameInstanceSubsystem.h"

#include "Weapons/BaseProjectile.h"
#include "TimerManager.h"


bool UActorPoolGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const 
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}
	return false;
}


void UActorPoolGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection) 
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("ObjectPoolSubsystem has been initialized"));
	
	
	GetWorld()->GetTimerManager().SetTimer
			(
			PopulatePoolTimerHandle, 
			this,
			&UActorPoolGameInstanceSubsystem::Init,       
			2.0f,               
			false
			);
	
	debugevent();
}


void UActorPoolGameInstanceSubsystem::Init()
{
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr; 
	SpawnParams.Instigator = nullptr; 
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int i = 0; i < PoolSize; i++)
	{
		ABaseProjectile* NewActor = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, FTransform(FVector::ZeroVector), SpawnParams);

		ProjectilePool.Add(NewActor);
		
	}
}



UWorld* UActorPoolGameInstanceSubsystem::GetWorld() const
{
	UGameInstance* MyGameInstance = GetGameInstance();
	if (MyGameInstance)
		return MyGameInstance->GetWorld();
	UE_LOG(LogTemp, Error, TEXT("Game Instance has a nullptr, please check Project Settings"));
	
	return nullptr;
}


void UActorPoolGameInstanceSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("ObjectPoolSubsystem has been deinitialized"));
	Super::Deinitialize();
}


ABaseProjectile* UActorPoolGameInstanceSubsystem::SpawnProjectileFromPool
	(
	UObject* WorldContextObject,
	AActor* Requester,
	AActor* Weapon,
	FTransform Transform
	)
{
	for(ABaseProjectile* Projectile : ProjectilePool)
	{
		if (Projectile && !Projectile->bIsActive)
		{	
			Projectile->SetActorTransform(Transform);
			Projectile->ActivateProjectile(Requester, Weapon);
			
			return Projectile;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No available Projectile to Pool, please modify ActorPoolSize parameter in Class Defaults"));
	return nullptr;
}