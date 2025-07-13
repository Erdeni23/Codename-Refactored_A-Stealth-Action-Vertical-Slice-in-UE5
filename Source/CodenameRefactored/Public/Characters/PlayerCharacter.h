// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "PlayerCharacter.generated.h"

//UE5 Native


//Custom
class UAdvancedMovementComponent;


UCLASS()
class CODENAMEREFACTORED_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();

protected:
	
    //Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAdvancedMovementComponent> AdvancedMovementComponent;
	
	//Functions
	virtual void BeginPlay() override;

	//Variables
	FVector2D MovementVector;
	FVector2D MouseLookVector;
	
	float ForwardVectorInputValue = 0.0f; //Прокси-переменная для передачи MovementVector.Y в спринт

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UpgradableStats)
	float MaxSprintSpeed = 900.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UpgradableStats)
	float DefaultSpeed = 600.0f;

public:
	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
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
	

};
