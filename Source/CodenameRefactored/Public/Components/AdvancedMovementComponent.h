// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdvancedMovementComponent.generated.h"

class ACharacter;
class UCharacterMovementComponent;
class UCapsuleComponent;
class UPlayerCameraManager;
class UCameraComponent;


UCLASS( ClassGroup=(Movement), meta=(BlueprintSpawnableComponent) )
class CODENAMEREFACTORED_API UAdvancedMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAdvancedMovementComponent();

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	ACharacter* OwnerCharacter;
	
	UPROPERTY()
	UCharacterMovementComponent* OwnerMovementComponent;

	UPROPERTY()
	APlayerCameraManager* PlayerCameraManager;

	FTimerHandle Delay;

	


	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
