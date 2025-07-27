// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"

#include "BaseWeapon.generated.h"


class USkeletalMeshComponent;
class UCapsuleComponent;
class GameInstance;
class UActorPoolGameInstanceSubsystem;
class UAnimMontage;

UCLASS(Blueprintable)
class CODENAMEREFACTORED_API ABaseWeapon :
public AActor,
public IInteractInterface

{
	GENERATED_BODY()
	
public:
	
	ABaseWeapon();

	//Functions
	UFUNCTION(BlueprintCallable)
	void ShootWeapon(const FTransform& Transform);
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual bool CanReload() const;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon();
	
	UFUNCTION(BlueprintCallable)
	void UnequipWeapon();

	UFUNCTION(BlueprintCallable)
	void DropWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void FinishReload();

	TObjectPtr<UAnimMontage> GetReloadMontage();

	float GetFireRate() const;

	//Start of IInteractInterface
	virtual void Interact_Implementation(USkeletalMeshComponent* SkeletalMeshComponent = nullptr, bool bEquip = false) override;
	//End of IInteractInterface


	
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponParameters)
	TObjectPtr<UAnimMontage> ReloadMontage;
	
	//Functions
	virtual void BeginPlay() override;
	

	//Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponParameters)
	float FireRate = 2000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponParameters)
	float MaxAmmo = 30.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponParameters)
	float CurrentAmmo = 30.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponParameters);
	FName AttachmentSocket;

	FAttachmentTransformRules AttachmentRules =
	{
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		true
	};

	FDetachmentTransformRules DetachmentRules =
	{
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld,
		true
	};
	
};
