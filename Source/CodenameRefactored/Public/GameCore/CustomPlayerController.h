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
	TObjectPtr<APlayerCharacter> PlayerCharacter;
	
	//Input
	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	TObjectPtr<UInputMappingContext> MouseLookMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	TObjectPtr<UInputAction> MouseLookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	TObjectPtr<UInputAction> CrouchSlideAction;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input")
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem;

	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

	//Functions

	virtual void OnPossess(APawn* CurrentPawn) override;

public:
	//Functions
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
};
