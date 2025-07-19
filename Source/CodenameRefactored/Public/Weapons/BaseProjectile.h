// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseProjectile.generated.h"


class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class UActorPoolGameInstanceSubsystem;

UCLASS(Blueprintable)
class CODENAMEREFACTORED_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseProjectile();

	//Variables
	UPROPERTY()
	bool bIsActive;

	int32 ProjectileIndex = INDEX_NONE;

	//Functions
	UFUNCTION()
	virtual void ActivateProjectile(AActor* Requester = nullptr, AActor* Weapon = nullptr);

	UFUNCTION()
	virtual void DeactivateProjectile();
	
protected:
	
	//Components
	UPROPERTY()
	TObjectPtr<UActorPoolGameInstanceSubsystem> ActorPoolSubsystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY()
	TArray<UPrimitiveComponent*> ComponentsToIgnore;

	FTimerHandle TimeToLiveTimer;

	//Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Speed = 8000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeToLive = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float GravityScale = 0.0f;

	UPROPERTY()
	AActor* CurrentWeapon;

	//Functions		
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit
		(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
		);


public:	

	
};
