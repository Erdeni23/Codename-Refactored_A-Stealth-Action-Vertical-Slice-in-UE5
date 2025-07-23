// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GASCharacter.h"
#include "Interfaces/ActorPoolInterface.h"

#include "PlayerCharacter.generated.h"

//UE5 Native

//Custom
class UAdvancedMovementComponent;

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

    //Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAdvancedMovementComponent> AdvancedMovementComponent;

	//Variables
	FVector2D MovementVector;
	
	FVector2D MouseLookVector;
	
	float ForwardVectorInputValue = 0.0f; //Прокси-переменная для передачи MovementVector.Y в спринт

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UpgradableStats)
	float MaxSprintSpeed = 900.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UpgradableStats)
	float DefaultSpeed = 600.0f;
	
	// Gameplay Ability System 
public:

};
