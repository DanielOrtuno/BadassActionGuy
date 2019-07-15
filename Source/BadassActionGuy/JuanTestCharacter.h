// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "JuanTestCharacter.generated.h"

UCLASS()
class BADASSACTIONGUY_API AJuanTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJuanTestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	FName GetAttachPointName() const;

	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool HasWeapon() const;

protected:
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void EquipWeapon(AWeaponBase* NewWeapon);

private:
	void EquipDefaultWeapon();


	void ThrowWeapon();

	void StartFire();

	void StopFire();

private:
	AWeaponBase* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = DefaultSettings)
	TSubclassOf<AWeaponBase> DefaultWeapon;

	UPROPERTY(EditDefaultsOnly, Category = DefaultSettings)
	FName AttachPointName;
};
