// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Weapons/BaseProjectile.h"

//UE5 Native
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"


ABaseProjectile::ABaseProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	/* Устанавливаем коллизию как Root Component для того,
	 * чтобы ProjectileMovementComponent корректно работал при вводе/выводе из пула */
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionProfileName(TEXT("Projectile"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;

	
}

void ABaseProjectile::ActivateProjectile(AActor* Requester, AActor* Weapon)
{
	
	if (!Requester || !Weapon)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: %s has a nullptr as a Requester or a Weapon"), *GetName());
		return;
	}

	bIsActive = true;

	//Включение расчета логики для снаряда если активен
	BoxCollision->IgnoreActorWhenMoving(Requester, bIsActive);
	BoxCollision->IgnoreActorWhenMoving(Weapon, bIsActive);
	
	SetActorEnableCollision(bIsActive);
	SetActorTickEnabled(bIsActive);
	SetActorHiddenInGame(!bIsActive);
	
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * speed;
	ProjectileMovementComponent->Activate();

	//очищаем таймер, который мог остаться с прошлого цикла пула
	GetWorld()->GetTimerManager().ClearTimer(TimeToLiveTimer);
	GetWorld()->GetTimerManager().SetTimer
	(
	TimeToLiveTimer,							
	[this]()
	{
		DeactivateProjectile();
	},
	timeToLive,                    
	false
	);
	
}

void ABaseProjectile::DeactivateProjectile()
{
	bIsActive = false;

	//Отключение расчета логики для снаряда если неактивен
	BoxCollision->ClearMoveIgnoreActors();
	
	SetActorEnableCollision(bIsActive);
	SetActorTickEnabled(bIsActive);
	SetActorHiddenInGame(!bIsActive);
	
	ProjectileMovementComponent->Velocity = {0,0,0};
	ProjectileMovementComponent->Deactivate();

}


void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	DeactivateProjectile();
	
}


// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

