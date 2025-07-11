// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


class UCapsuleComponent;
class UPlayerCameraManager;
class UCharacterMovementComponent;
class UCameraComponent;


UCLASS()
class CODENAMEREFACTORED_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();

protected:
	
    //Components
	UPROPERTY(BlueprintReadOnly, Category = "Components")
	APlayerCameraManager* PlayerCameraManager;

	//Variables
	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsSliding = false;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsStandingUp = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CameraBounds")
	float defaultCameraViewPitchMax = 80.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CameraBounds")
	float defaultCameraViewPitchMin = -75.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CameraBounds")
	float defaultCameraViewYawMax = 359.998291f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CameraBounds")
	float defaultCameraViewYawMin = 0.0f;
	
	FTimerHandle Delay;
	
	//Functions
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SlideCrouch();

	UFUNCTION(BlueprintCallable)
	void CrouchSlideCompleted();
	
	void DoCrouch();


public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
