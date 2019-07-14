// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BADASSACTIONGUY_API AMeleeWeapon : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AMeleeWeapon();

protected:
	//virtual void OnStartFire() override;

	//virtual void OnStopFire() override;
};
