// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ActorPoolInterface.h"

#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class GameInstance;
class UActorPoolGameInstanceSubsystem;


UCLASS(Blueprintable)
class CODENAMEREFACTORED_API ABaseWeapon : public AActor, public IActorPoolInterface
{
	GENERATED_BODY()
	
public:
	
	ABaseWeapon();

	//Functions
	UFUNCTION(BlueprintCallable)
	void ShootWeapon(const FTransform& Transform);
	
	UFUNCTION(BlueprintCallable)
	void PickUp
		(
		USkeletalMeshComponent* OwnerSkeletalMeshComponent,
		bool bEquip
		);

	//Variables
	FAttachmentTransformRules AttachmentRules =
	{
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		true
	};
	
protected:

	//Components
	UPROPERTY()
	TObjectPtr<UGameInstance> GameInstance;

	UPROPERTY()
	TObjectPtr<UActorPoolGameInstanceSubsystem> ActorPoolSubsystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	
	UPROPERTY()
	TObjectPtr<AActor> GunOwner;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OwnerSkeletalMesh;

	UPROPERTY()
	TObjectPtr<UCapsuleComponent> OwnerCapsule;
	
	//Functions
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void EquipWeapon(USceneComponent* OwnerSkeletalMeshComponent);

	//Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponParameters);
	FName AttachmentSocket;

public:
	
	
	
};
