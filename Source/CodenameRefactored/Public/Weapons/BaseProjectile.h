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

	//Variables
	UPROPERTY()
	bool bIsActive;

	//Functions
	UFUNCTION()
	virtual void ActivateProjectile(AActor* Requester = nullptr, AActor* Weapon = nullptr);
	
protected:
	
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	FTimerHandle TimeToLiveTimer;

	//Variables


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float speed = 8000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float timeToLive = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float gravityScale = 0.0f;

	//Functions		
	virtual void BeginPlay() override;



	UFUNCTION()
	virtual void DeactivateProjectile(AActor* Weapon = nullptr);

	

public:	

	virtual void Tick(float DeltaTime) override;
	
};
