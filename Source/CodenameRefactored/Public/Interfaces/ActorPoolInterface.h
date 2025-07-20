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
	void ReturnProjectileToPool(ABaseProjectile* Projectile);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Actor Pool")
	TArray<UPrimitiveComponent*> GetComponentsToIgnoreForCollision() const;
	
};
