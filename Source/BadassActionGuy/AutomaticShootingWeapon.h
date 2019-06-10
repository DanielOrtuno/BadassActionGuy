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
};
