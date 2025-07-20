// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "Weapons/BaseProjectile.h"

//UE5 Native
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"

//Custom
#include "Subsystems/ActorPoolGameInstanceSubsystem.h"
#include "Interfaces/ActorPoolInterface.h"


ABaseProjectile::ABaseProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = false;

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

	ProjectileMovementComponent->ProjectileGravityScale = GravityScale;
	ProjectileMovementComponent->bShouldBounce = false;
	
}


void ABaseProjectile::ActivateProjectile(AActor* Requester, AActor* Weapon)
{
	
	if (!Weapon)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has a nullptr as a Weapon"), *GetName());
		return;
	}
	if (!Requester )
	{
		UE_LOG(LogTemp, Error, TEXT("%s has a nullptr as a Requester"), *GetName());
		return;
	}
	
	bIsActive = true;
	
	CurrentWeapon = Weapon;
	SetOwner(Requester);

	//Компоненты пули игнорируют Стрелка, Компоненты стрелка игнорируют пулю
	BoxCollision->IgnoreActorWhenMoving(Requester, bIsActive);
	BoxCollision->IgnoreActorWhenMoving(CurrentWeapon, bIsActive);

	ComponentsToIgnore = IActorPoolInterface::Execute_GetComponentsToIgnoreForCollision(Requester);
	for (UPrimitiveComponent* Component : ComponentsToIgnore)
	{
		if (Component)
			Component->IgnoreActorWhenMoving(this, true);
	}
	
	//Включение расчета логики для снаряда если активен
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * Speed;
	ProjectileMovementComponent->Activate();
	
	SetActorEnableCollision(bIsActive);
	SetActorHiddenInGame(!bIsActive);
	
	//очищаем таймер, который мог остаться с прошлого цикла пула
	GetWorld()->GetTimerManager().ClearTimer(TimeToLiveTimer);
	
	GetWorld()->GetTimerManager().SetTimer
	(
	TimeToLiveTimer,							
	this,
	&ABaseProjectile::DeactivateProjectile,
	TimeToLive,                    
	false
	);
	
}


void ABaseProjectile::DeactivateProjectile()
{
	BoxCollision->IgnoreActorWhenMoving(GetOwner(), false);
	BoxCollision->IgnoreActorWhenMoving(CurrentWeapon, false);
	
	for (UPrimitiveComponent* Component : ComponentsToIgnore)
	{
		if (Component)
			Component->IgnoreActorWhenMoving(this, false);
	}
	ComponentsToIgnore.Empty();
	
	if (bIsActive)
		IActorPoolInterface::Execute_ReturnProjectileToPool(ActorPoolSubsystem,this);
	
	bIsActive = false;

	//Отключение расчета логики для снаряда если неактивен
	SetActorEnableCollision(bIsActive);
	SetActorHiddenInGame(!bIsActive);
	
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	ProjectileMovementComponent->Deactivate();
	
	CurrentWeapon = nullptr;

}


void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	ActorPoolSubsystem = GetGameInstance()->GetSubsystem<UActorPoolGameInstanceSubsystem>();
	BoxCollision->OnComponentHit.AddDynamic(this,&ABaseProjectile::OnHit);
	
}


void ABaseProjectile::OnHit
	(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, 
	const FHitResult& Hit
	) 
{
	DeactivateProjectile();
	
}



