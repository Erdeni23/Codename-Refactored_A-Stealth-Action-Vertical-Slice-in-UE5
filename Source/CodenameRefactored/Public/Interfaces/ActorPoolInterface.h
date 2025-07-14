// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorPoolInterface.generated.h"


UINTERFACE(MinimalAPI)
class UActorPoolInterface : public UInterface
{
	GENERATED_BODY()
};


class CODENAMEREFACTORED_API IActorPoolInterface
{
	GENERATED_BODY()

public:
	//Для снарядов, класс BaseProjectile в Weapons/BaseProjectile
	UFUNCTION(BlueprintNativeEvent, Category = "Actor Pool")
	void SpawnProjectileFromPool(AActor* Requester, AActor* Weapon, FTransform Transform);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actor Pool")
	void ProjectileWasReturnedToPool(AActor* Projectile );

	UFUNCTION(BlueprintNativeEvent, Category = "Actor Pool")
	void PooledProjectileReference(AActor* Projectile);
	

public:
};
