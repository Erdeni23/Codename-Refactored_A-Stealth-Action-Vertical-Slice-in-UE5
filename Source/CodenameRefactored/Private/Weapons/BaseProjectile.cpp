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
	
	BoxCollision->IgnoreActorWhenMoving(Requester, bIsActive);
	BoxCollision->IgnoreActorWhenMoving(CurrentWeapon, bIsActive);

	//Включение расчета логики для снаряда если активен
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * speed;
	ProjectileMovementComponent->Activate();
	
	SetActorEnableCollision(bIsActive);
	SetActorTickEnabled(bIsActive);
	SetActorHiddenInGame(!bIsActive);
	
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
	
	BoxCollision->ClearMoveIgnoreActors();
	bIsActive = false;

	//Отключение расчета логики для снаряда если неактивен
	SetActorEnableCollision(bIsActive);
	SetActorTickEnabled(bIsActive);
	SetActorHiddenInGame(!bIsActive);
	
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	ProjectileMovementComponent->Deactivate();

	if (CurrentWeapon)
		IActorPoolInterface::Execute_ProjectileWasReturnedToPool(CurrentWeapon, this);
	
	CurrentWeapon = nullptr;
	
}


void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	DeactivateProjectile();

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
	if (OtherActor)
		OtherActor->Destroy(); //плейсхолдер до введения системы урона
	Hit.BoneName;
	NormalImpulse;
	HitComponent;
	DeactivateProjectile();
	
}


// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

