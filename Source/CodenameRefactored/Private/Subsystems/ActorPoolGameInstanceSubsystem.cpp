// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#include "Subsystems/ActorPoolGameInstanceSubsystem.h"

#include "Weapons/BaseProjectile.h"
#include "Interfaces/ActorPoolInterface.h"



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
	Init();
}


UWorld* UActorPoolGameInstanceSubsystem::GetWorld() const
{
	UGameInstance* MyGameInstance = GetGameInstance();
	if (MyGameInstance)
	{
		return MyGameInstance->GetWorld();
	}
	return nullptr;
}


void UActorPoolGameInstanceSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("ObjectPoolSubsystem has been deinitialized"));
	Super::Deinitialize();
}


AActor* UActorPoolGameInstanceSubsystem::SpawnProjectileFromPool
	(
	UObject* WorldContextObject,
	AActor* Requester,
	AActor* Weapon,
	FTransform Transform,
	const TArray<ABaseProjectile*>& ActorPool
	)
{
	for(ABaseProjectile* Projectile : ActorPool)
	{
		if (Projectile && !Projectile->bIsActive)
		{
			Projectile->SetActorTransform(Transform);
			Projectile->ActivateProjectile(Requester, Weapon);
			IActorPoolInterface::Execute_PooledProjectileReference(Weapon,Projectile);
			
			/*интерфейс для передачи оружию информации о снаряде выпущенным Requester'ом
			нужно для правильной работы коллизии 
			*/
			
			return Projectile;
		}
	}
	return nullptr;
}