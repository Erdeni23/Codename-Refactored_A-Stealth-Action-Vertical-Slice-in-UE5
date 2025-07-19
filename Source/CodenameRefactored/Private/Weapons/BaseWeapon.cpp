// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Weapons/BaseWeapon.h"
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

void ABaseWeapon::PickUp(USkeletalMeshComponent* OwnerSkeletalMeshComponent, bool bEquip)
{
	OwnerSkeletalMesh = OwnerSkeletalMeshComponent;
	SetOwner(OwnerSkeletalMeshComponent->GetOwner());
	GunOwner = GetOwner();
	
	if (bEquip)
		EquipWeapon(OwnerSkeletalMeshComponent);
	
}


void ABaseWeapon::ShootWeapon(const FTransform& Transform)
{
	AActor* Projectile = ActorPoolSubsystem->SpawnProjectileFromPool(GunOwner, this, Transform);
	
	if (!Projectile)
		UE_LOG(LogTemp, Warning, TEXT("Projectile has a nullptr! Please modify Actor Pool Size!"));
	
}

void ABaseWeapon::EquipWeapon(USceneComponent* OwnerSkeletalMeshComponent)
{
	SetActorHiddenInGame(false);
	AttachToComponent(OwnerSkeletalMeshComponent, AttachmentRules, AttachmentSocket);
}
