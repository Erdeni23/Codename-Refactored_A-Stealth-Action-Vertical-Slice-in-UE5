// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class GameInstance;
class UActorPoolGameInstanceSubsystem;


UCLASS(Blueprintable)
class CODENAMEREFACTORED_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	
	ABaseWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UFUNCTION(BlueprintCallable)
	void InitiateWeapon(USkeletalMeshComponent* OwnerSkeletalMeshComponent, UCapsuleComponent* OwnerCapsuleComponent);

	UFUNCTION(BlueprintCallable)
	void ShootWeapon(FTransform Transform);

	UFUNCTION(BlueprintImplementableEvent)
	void somethingsomething();
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AActor> GunOwner;

	UPROPERTY()
	TObjectPtr<UGameInstance> GameInstance;

	UPROPERTY()
	TObjectPtr<UActorPoolGameInstanceSubsystem> ActorPoolSubsystem;
	
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OwnerSkeletalMesh;

	UPROPERTY()
	TObjectPtr<UCapsuleComponent> OwnerCapsule;	

public:
	
	virtual void Tick(float DeltaTime) override;

};
