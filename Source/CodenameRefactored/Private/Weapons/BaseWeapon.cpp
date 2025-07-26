// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Weapons/BaseWeapon.h"
#include "Subsystems/ActorPoolGameInstanceSubsystem.h"
#include "Animation/AnimMontage.h"


ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	
}


void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstance = GetGameInstance();
	ActorPoolSubsystem = GameInstance->GetSubsystem<UActorPoolGameInstanceSubsystem>();
	CurrentAmmo = MaxAmmo;
}


void ABaseWeapon::ShootWeapon(const FTransform& Transform)
{
	if (CurrentAmmo > 0)
	{
		AActor* Projectile = ActorPoolSubsystem->SpawnProjectileFromPool(GunOwner, this, Transform);
	
		if (!Projectile)
			UE_LOG(LogTemp, Warning, TEXT("Projectile has a nullptr! Please modify Actor Pool Size!"));

		CurrentAmmo -=1;
	}
	
}


void ABaseWeapon::EquipWeapon()
{
	TObjectPtr<USceneComponent> OwnerAttachableComponent = OwnerSkeletalMesh;
	SetActorHiddenInGame(false);
	AttachToComponent(OwnerAttachableComponent, AttachmentRules, AttachmentSocket);
	
}


void ABaseWeapon::UnequipWeapon()
{
	DetachFromActor(DetachmentRules);
	SetActorHiddenInGame(true);
}


void ABaseWeapon::DropWeapon()
{
	SetActorHiddenInGame(false);
	DetachFromActor(DetachmentRules);
	SetOwner(nullptr);
}


void ABaseWeapon::Interact_Implementation(USkeletalMeshComponent* SkeletalMeshComponent, bool bEquip)
{
	OwnerSkeletalMesh = SkeletalMeshComponent;
	SetOwner(SkeletalMeshComponent->GetOwner());
	GunOwner = GetOwner();
	
	if (bEquip)
		EquipWeapon();
	else
		UnequipWeapon();
		
}


void ABaseWeapon::FinishReload()
{
	CurrentAmmo = MaxAmmo;
}


bool ABaseWeapon::CanReload() const
{
	return ((CurrentAmmo < MaxAmmo) && (MaxAmmo > 0));
}


float ABaseWeapon::GetFireRate() const
{
	return FireRate;
}



