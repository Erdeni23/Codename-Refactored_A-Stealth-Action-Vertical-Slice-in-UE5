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

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;

	
}

void ABaseProjectile::InUse(bool bIsInUse = false, AActor* Requester, AActor* Weapon)
{
	TObjectPtr<AActor> SafeRequester = Requester;
	TObjectPtr<AActor> SafeWeapon = Weapon;
	
	if (!SafeRequester || !SafeWeapon)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: %s has a nullptr"), *GetOwner()->GetName())
		return;
	}

	bIsActive = true;

	//Отключение расчета логики для снаряда если неактивен
	BoxCollision->IgnoreActorWhenMoving(SafeRequester, bIsActive);
	BoxCollision->IgnoreActorWhenMoving(SafeWeapon, bIsActive);
	SetActorEnableCollision(bIsActive);
	SetActorTickEnabled(bIsActive);
	SetActorHiddenInGame(!bIsActive);

	if (bIsActive)
	{
		ProjectileMovementComponent->Velocity = GetActorForwardVector() * speed;
		ProjectileMovementComponent->Activate();
	}
	else
	{
		ProjectileMovementComponent->Velocity = {0,0,0};
		ProjectileMovementComponent->Deactivate();

		GetWorld()->GetTimerManager().SetTimer(
		TimeToLiveTimer,							
		this,								
		&ABaseProjectile::ReturnToPool,
		timeToLive,                    
		false);
	}
	

}

void ABaseProjectile::ReturnToPool()
{
	InUse();
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

