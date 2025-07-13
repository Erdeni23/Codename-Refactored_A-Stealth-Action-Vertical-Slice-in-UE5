// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class AActor;


UCLASS(Blueprintable)
class CODENAMEREFACTORED_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseProjectile();

	
protected:
	
	//Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	FTimerHandle TimeToLiveTimer;

	//Variables
	UPROPERTY()
	bool bIsActive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float speed = 8000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float timeToLive = 2.0f;

	//Functions		
	virtual void BeginPlay() override;

	UFUNCTION()
	void InUse(bool bIsInUse, AActor* Requester = nullptr, AActor* Weapon = nullptr);

	UFUNCTION()
	void ReturnToPool();

public:	

	virtual void Tick(float DeltaTime) override;

	

};
