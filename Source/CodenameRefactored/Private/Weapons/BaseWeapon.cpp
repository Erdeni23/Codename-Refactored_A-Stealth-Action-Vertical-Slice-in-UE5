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
	
}

//при спавне обязательно!
void ABaseWeapon::InitiateWeapon(USkeletalMeshComponent* OwnerSkeletalMeshComponent, UCapsuleComponent* OwnerCapsuleComponent)
{
	OwnerSkeletalMesh = OwnerSkeletalMeshComponent;
	OwnerCapsule = OwnerCapsuleComponent;
	GunOwner = GetOwner();

	GameInstance = GetGameInstance();
	ActorPoolSubsystem = GameInstance->GetSubsystem<UActorPoolGameInstanceSubsystem>();
	
}


void ABaseWeapon::ShootWeapon(FTransform Transform)
{
	AActor* Projectile = ActorPoolSubsystem->SpawnProjectileFromPool(GunOwner, this, Transform);

	if (!Projectile)
		return;
	
	SkeletalMesh->IgnoreActorWhenMoving(Projectile, true);
	OwnerSkeletalMesh->IgnoreActorWhenMoving(Projectile, true);
	OwnerCapsule->IgnoreActorWhenMoving(Projectile, true);
	
}


void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::ProjectileWasReturnedToPool_Implementation(AActor* ProjectileToReturn)
{
	if (!ProjectileToReturn)
		return;
	
	SkeletalMesh->IgnoreActorWhenMoving(ProjectileToReturn, false);
	OwnerSkeletalMesh->IgnoreActorWhenMoving(ProjectileToReturn, false);
	OwnerCapsule->IgnoreActorWhenMoving(ProjectileToReturn, false);
	
}
