// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Subsystems/ActorPoolGameInstanceSubsystem.h"

#include "Weapons/BaseProjectile.h"
#include "TimerManager.h"
#include "Containers/Queue.h"

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
			TimerHandle, 
			this,
			&UActorPoolGameInstanceSubsystem::Init,       
			2.0f,               
			false
			);
	
}


void UActorPoolGameInstanceSubsystem::Init()
{
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr; 
	SpawnParams.Instigator = nullptr; 
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int i = 0; i < PoolSize; i++)
	{
		ABaseProjectile* ProjectileObject = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, FTransform(FVector::ZeroVector), SpawnParams);
		ProjectileObject->DeactivateProjectile();
		ProjectilePool.Add(ProjectileObject);
		FreeActorIndexes.Enqueue(i);
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


AActor* UActorPoolGameInstanceSubsystem::SpawnProjectileFromPool
	(
	AActor* Requester,
	AActor* Weapon,
	const FTransform& Transform
	)
{
	if (FreeActorIndexes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No available Projectile to Pool, please modify ActorPoolSize parameter in Class Defaults"));
		return nullptr;
	}
	int32 PooledIndex;
	FreeActorIndexes.Dequeue(PooledIndex);
	ABaseProjectile* CurrentProjectile = ProjectilePool[PooledIndex];

	CurrentProjectile->ProjectileIndex = PooledIndex;
	CurrentProjectile->SetActorTransform(Transform);
	CurrentProjectile->ActivateProjectile(Requester, Weapon);
			
	return CurrentProjectile;

}


void UActorPoolGameInstanceSubsystem::ReturnProjectileToPool_Implementation(ABaseProjectile* Projectile)
{
	int32 ReturnIndex = Projectile->ProjectileIndex;
	FreeActorIndexes.Enqueue(ReturnIndex); 
	
}