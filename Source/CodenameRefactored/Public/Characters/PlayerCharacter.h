// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//components
#include "Camera/CameraComponent.h"


#include "PlayerCharacter.generated.h"



UCLASS()
class CODENAMEREFACTORED_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerCamera")
	UCameraComponent* PlayerCamera;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
