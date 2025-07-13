// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdvancedMovementComponent.generated.h"

class ACharacter;
class APlayerController;
class UCharacterMovementComponent;
class UCapsuleComponent;
class UPlayerCameraManager;


UCLASS( ClassGroup=(Movement), meta=(BlueprintSpawnableComponent) )
class CODENAMEREFACTORED_API UAdvancedMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAdvancedMovementComponent();

protected:
	
	//Функции
	virtual void BeginPlay() override;
	
	//Переменные, доступные через блюпринты для Чтения/ЧтенияЗаписи

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsSliding = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|CameraBounds")
	float DefaultCameraViewPitchMax = 80.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|CameraBounds")
	float DefaultCameraViewPitchMin = -75.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|CameraBounds")
	float DefaultCameraViewYawMax = 359.998291f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|CameraBounds")
	float DefaultCameraViewYawMin = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|CrouchSlide")
	float MinSpeedForSlide = 800.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|CrouchSlide")
	float CrouchedCapsuleRadius = 60.0f;

	
private:
	
	//Данные о владельце/компоненты
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;
	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwnerMovementComponent = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerCameraManager> PlayerCameraManager = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerController> OwnerPlayerController = nullptr;

	UPROPERTY()
	TObjectPtr<UCapsuleComponent> OwnerCapsuleComponent = nullptr;
	
	UPROPERTY()
	FTimerHandle Delay;
	
	//Переменные
	UPROPERTY()
	int32 OwnerPlayerIndex = -1;


public:


	void CrouchSlideBegin();
	
	void DoCrouch();
	
	void CrouchSlideCompleted();

	void SlideCompleted();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
