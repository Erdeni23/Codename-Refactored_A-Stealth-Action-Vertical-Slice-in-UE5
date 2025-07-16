// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Weapons/BaseProjectile.h"

//UE5 Native
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"

//Custom
#include "Interfaces/ActorPoolInterface.h"


ABaseProjectile::ABaseProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	/* Устанавливаем коллизию как Root Component для того,
	 * чтобы ProjectileMovementComponent корректно работал при вводе/выводе из пула */
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent->SetMobility(EComponentMobility::Movable); 



	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;

	ProjectileMovementComponent->ProjectileGravityScale = gravityScale;
	ProjectileMovementComponent->bShouldBounce = false;
	
	
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
	[this, Weapon]()
	{
		DeactivateProjectile(Weapon);
	},
	timeToLive,                    
	false
	);
	
}


void ABaseProjectile::DeactivateProjectile(AActor* Weapon)
{
	
	bIsActive = false;

	BoxCollision->ClearMoveIgnoreActors();
	
	//Отключение расчета логики для снаряда если неактивен
	SetActorEnableCollision(bIsActive);
	SetActorTickEnabled(bIsActive);
	SetActorHiddenInGame(!bIsActive);
	
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	ProjectileMovementComponent->Deactivate();

	//отправляем референс оружию, для настройки коллизии
	if (Weapon)
		IActorPoolInterface::Execute_ProjectileWasReturnedToPool(Weapon,this);
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

