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

	FWeaponConfig()
	{
		MaxAmmo = 100;
		AmmoPerClip = 25;
		InitialClips = 2;
	}
};

UCLASS()
class BADASSACTIONGUY_API AShootingWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	AShootingWeapon();

private:
	/** Structure holding weapon configuration */
	FWeaponConfig WeaponConfig;
};
