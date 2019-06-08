// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BADASSACTIONGUY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

/********************
* Member Variables  
********************/

private:
	UPROPERTY(EditAnywhere)
	float SpeedModifier;

	UPROPERTY(EditAnywhere)
	float SlowModifier;

	UPROPERTY(EditAnywhere)
	float MaxSlowMoTime;

	UPROPERTY(EditAnywhere)
	float SlowMoRechargeDelay;

	UPROPERTY()
	float SlowMoTime;

	UPROPERTY()
	float SlowMoRechargeTimer;

/********************
* Member Functions
********************/

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Fire();

	void StartSlowMo();

	void StopSlowMo();

	void StartSprint();

	void StopSprint();
};
