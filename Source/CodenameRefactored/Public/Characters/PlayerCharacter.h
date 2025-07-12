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
	UAdvancedMovementComponent* AdvancedMovementComponent;
	
	
	//Functions
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SlideCrouch();

	UFUNCTION(BlueprintCallable)
	void UnSlideCrouch();

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
