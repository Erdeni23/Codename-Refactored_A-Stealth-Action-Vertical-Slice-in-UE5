// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Weapons/BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Subsystems/ActorPoolGameInstanceSubsystem.h"


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
	
	
}

void ABaseWeapon::PickUp(USkeletalMeshComponent* OwnerSkeletalMeshComponent, UCapsuleComponent* OwnerCapsuleComponent, bool bEquip)
{
	OwnerSkeletalMesh = OwnerSkeletalMeshComponent;
	OwnerCapsule = OwnerCapsuleComponent;
	SetOwner(OwnerSkeletalMeshComponent->GetOwner());
	GunOwner = GetOwner();
	
	if (bEquip)
		EquipWeapon(OwnerSkeletalMeshComponent);
	
}


void ABaseWeapon::ShootWeapon(const FTransform& Transform)
{
	AActor* Projectile = ActorPoolSubsystem->SpawnProjectileFromPool(GunOwner, this, Transform);

	if (!Projectile)
		return;
	
	SkeletalMesh->IgnoreActorWhenMoving(Projectile, true);
	OwnerSkeletalMesh->IgnoreActorWhenMoving(Projectile, true);
	OwnerCapsule->IgnoreActorWhenMoving(Projectile, true);
	
}

void ABaseWeapon::EquipWeapon(USceneComponent* OwnerSkeletalMeshComponent)
{
	SetActorHiddenInGame(false);
	AttachToComponent(OwnerSkeletalMeshComponent, AttachmentRules, AttachmentSocket);
}


void ABaseWeapon::ProjectileWasReturnedToPool_Implementation(AActor* ProjectileToReturn)
{
	if (!ProjectileToReturn)
		return;
	
	SkeletalMesh->IgnoreActorWhenMoving(ProjectileToReturn, false);
	OwnerSkeletalMesh->IgnoreActorWhenMoving(ProjectileToReturn, false);
	OwnerCapsule->IgnoreActorWhenMoving(ProjectileToReturn, false);
	
}
