// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Weapons/BaseProjectile.h"

//UE5 Native
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ABaseProjectile::ABaseProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	/* Устанавливаем коллизию как Root Component для того,
	 * чтобы ProjectileMovementComponent корректно работал при вводе/выводе из пула */
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;

	
}

void ABaseProjectile::InUse()
{
	bIsActive = true;


}



void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

