// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ActorPoolInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"




#include "ActorPoolGameInstanceSubsystem.generated.h"

class ABaseProjectile;


UCLASS(Blueprintable)
class CODENAMEREFACTORED_API UActorPoolGameInstanceSubsystem : public UGameInstanceSubsystem, public IActorPoolInterface
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	virtual void ReturnProjectileToPool_Implementation(ABaseProjectile* Projectile) override;
	/*
	создаем проверку наличия сабсистемы на блюпринтах, для того чтобы иметь
	только одну инстанцию в игре
	*/
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	/*
	Переопределяем встроенную фунцкию GetWorld,
	для того, чтобы сабсистема имела, контекст WorldContext
	*/
	virtual UWorld* GetWorld() const override;

	/*
	Актор пул система, создается при инициалзации в BP_ActorPoolManager.
	Логика передачи/возврата актора исполнена здесь 
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject")) 
	AActor* SpawnProjectileFromPool
	   (
	   AActor* Requester,
	   AActor* Weapon,
	   const FTransform& Transform
	   );


protected:
	
	UFUNCTION()
	void Init();
	
	UPROPERTY()
	TArray<ABaseProjectile*> ProjectilePool;

	TQueue<int32> FreeActorIndexes;
	

	UPROPERTY(EditDefaultsOnly, Category = "Pool Settings")
	TSubclassOf<ABaseProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pool Settings")
	int32 PoolSize = 200;
	
	FTimerHandle TimerHandle;
	
protected:



private:

	


};