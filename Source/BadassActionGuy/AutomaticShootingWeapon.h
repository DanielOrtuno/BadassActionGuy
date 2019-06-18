// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootingWeapon.h"
#include "AutomaticShootingWeapon.generated.h"

USTRUCT()
struct FAutomaticWeaponConfig
{
	GENERATED_BODY()

	/** Time in seconds between two consecutive shots */
	float TimeBetweenShots;

	FAutomaticWeaponConfig()
	{
		TimeBetweenShots = 0.2f;
	}
};

/**
 * 
 */
UCLASS()
class BADASSACTIONGUY_API AAutomaticShootingWeapon : public AShootingWeapon
{
	GENERATED_BODY()
	
public:
	AAutomaticShootingWeapon();

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(BlueprintCallable, Category = Shooting)
	void OnStartFire();

	UFUNCTION(BlueprintCallable, Category = Shooting)
	void OnStopFire();

private:
	FTimerHandle FireHandle;

	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	FAutomaticWeaponConfig AutomaticWeaponConfig;
};
