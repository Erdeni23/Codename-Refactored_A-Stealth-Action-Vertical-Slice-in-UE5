// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

//UE5 Native
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

//UE5Custom


//Context
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputComponent;
class APlayerCharacter;

UCLASS()
class CODENAMEREFACTORED_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	//OwnerReferences
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
	//Input
	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	UInputMappingContext* MouseLookMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	UInputAction* MouseLookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	UInputAction* CrouchSlideAction;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	UInputAction* RunAction;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	UInputAction* ShootAction;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* Subsystem;

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

	//Functions

	virtual void OnPossess(APawn* CurrentPawn) override;

public:
	//Functions
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	
};
