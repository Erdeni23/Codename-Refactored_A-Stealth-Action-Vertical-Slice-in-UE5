// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"


#include "ActorPoolGameInstanceSubsystem.generated.h"

class ABaseProjectile;


UCLASS(Blueprintable)
class CODENAMEREFACTORED_API UActorPoolGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	/*
	создаем проверку наличия сабсистемы на блюпринтах, для того чтобы иметь
	только одну инстанцию в игре
	*/
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	/*
	Получаем данные World через указатель и встроенную фунцкию GetWorld,
	для того, чтобы сабсистема имела, контекст WorldContext
	*/
	virtual UWorld* GetWorld() const override;

protected:
	FTimerHandle PoolInitTimerHandle; 
	UFUNCTION()
	void Init();

	UFUNCTION(BlueprintImplementableEvent)
	void debugevent();


	UPROPERTY()
	TArray<ABaseProjectile*> ProjectilePool;
	


	UPROPERTY(EditDefaultsOnly, Category = "Pool Settings")
	TSubclassOf<ABaseProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pool Settings")
	int32 PoolSize = 200;
	
	/*
	Актор пул система, создается при инициалзации в BP_ActorPoolManager.
	Логика передачи/возврата актора исполнена здесь 
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject")) 
	 ABaseProjectile* SpawnProjectileFromPool
		(
		UObject* WorldContextObject,
		AActor* Requester,
		AActor* Weapon,
		FTransform Transform
		);

	
protected:



private:

	


};