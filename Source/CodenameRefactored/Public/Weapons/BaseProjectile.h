// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;



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

	//Variables
	bool bIsActive;
	

	//Functions		
	virtual void BeginPlay() override;

	void InUse();

	


public:	

	virtual void Tick(float DeltaTime) override;

	

};
