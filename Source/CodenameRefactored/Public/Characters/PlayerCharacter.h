// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GASCharacter.h"
#include "Interfaces/ActorPoolInterface.h"

#include "PlayerCharacter.generated.h"

//UE5 Native
class APlayerCameraManager;

//Custom
class UAdvancedMovementComponent;
class ABaseWeapon;


UCLASS()
class CODENAMEREFACTORED_API APlayerCharacter :
public AGASCharacter,
public IActorPoolInterface

{
	GENERATED_BODY()

public: 
	
	APlayerCharacter();

	//Functions
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interfaces
	
	//Start of IActorPoolInterface
	virtual TArray<UPrimitiveComponent*> GetComponentsToIgnoreForCollision_Implementation() const override;
	//End of IActorPoolInterface

	
	//Actions bind to Input
	UFUNCTION()
	void MouseLook(const FInputActionValue& MouseLookValue);

	UFUNCTION()
	void Move(const FInputActionValue& MovementValue);
	
	UFUNCTION()
	void SprintBegin();
	
	UFUNCTION()
	void SprintStop();
	
	UFUNCTION()
	void CrouchSlide();
	
	UFUNCTION()
	void UnCrouchSlide();

protected:

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AActor* InteractWithObject();
	
    //Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAdvancedMovementComponent> AdvancedMovementComponent;

	UPROPERTY()
	TObjectPtr<APlayerCameraManager> PlayerCameraManager;

	//Variables
	FVector2D MovementVector;
	
	FVector2D MouseLookVector;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionDistance = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionSphereRadius = 50.0f;
	
	float ForwardVectorInputValue = 0.0f; //Прокси-переменная для передачи MovementVector.Y в спринт

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UpgradableStats)
	float MaxSprintSpeed = 900.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UpgradableStats)
	float DefaultSpeed = 600.0f;
	
	// Gameplay Ability System 
public:

};
