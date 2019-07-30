// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "ShootingWeapon.generated.h"

USTRUCT()
struct FWeaponConfig
{
	GENERATED_BODY()

	/** Max ammo that can be carried in gun */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	int MaxAmmo;

	/** The amount of bullets that a clip can hold */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	int AmmoPerClip;

	/** Starting clips when initially equipped */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	int InitialClips;

	/** Time in seconds between two consecutive shots */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	float TimeBetweenShots;

	/** Wether the gun shoots continously when the fire button is pressed */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	bool bIsAutomatic;

	/** Max distance a bullet can travel */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	float Range;

	FWeaponConfig()
	{
		MaxAmmo = 100;
		AmmoPerClip = 25;
		InitialClips = 2;
		TimeBetweenShots = 0.2f;
		bIsAutomatic = false;
		Range = 10000.f;
	}
};

UCLASS()
class BADASSACTIONGUY_API AShootingWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	AShootingWeapon();

	/** The owner has pressed the trigger */
	virtual void OnStartFire() override;

	/** The owner has released the trigger */
	virtual void OnStopFire() override;

	/** Shoots a single bullet from the gun, if possible */
	void Fire();

private:
	/** Makes the weapon available for a new trigger press. Only used for non-automatic weapons */
	void SetTriggerReady();

private:
	/** Structure holding weapon configuration */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	FWeaponConfig WeaponConfig;

	/** The muzzle position for projectile instancing */
	UPROPERTY(EditDefaultsOnly, Category = Muzzle)
	FName Muzzle;

	/** The projectile that will be shot from the muzzle */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AActor> Projectile;

	/** The current number of clips available for the weapon */
	UPROPERTY(VisibleInstanceOnly, Category = Ammo)
	int AvailableClips;

	/** Ammo count inside the current clip */
	UPROPERTY(VisibleInstanceOnly, Category = Ammo)
	int AmmoInClip;

	/** Timer to handle the delay between shots */
	FTimerHandle ShotDelay;

	/** True if there is no pending delay from shots */
	bool bTriggerReady;
};
