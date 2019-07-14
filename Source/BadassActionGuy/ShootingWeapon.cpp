// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Public/TimerManager.h"

AShootingWeapon::AShootingWeapon()
{
	AvailableClips = WeaponConfig.InitialClips - 1;
	AmmoInClip = WeaponConfig.AmmoPerClip;

	bTriggerReady = true;
	EWeaponType::HandGun;
}

void AShootingWeapon::OnStartFire()
{
	if (bTriggerReady)
	{
		Fire();
		bTriggerReady = false;
		GetWorldTimerManager().SetTimer(ShotDelay, this, &AShootingWeapon::SetTriggerReady, WeaponConfig.TimeBetweenShots, false);
	}
}

void AShootingWeapon::Fire()
{
	if (AmmoInClip > 0)
	{
		const USkeletalMeshSocket* MuzzleSocket = WeaponMesh->GetSocketByName(Muzzle);
		GetWorld()->SpawnActor<AActor>(Projectile, MuzzleSocket->GetSocketTransform(WeaponMesh));

		AmmoInClip--;
	}

	else if (AvailableClips > 0)
	{
		AvailableClips--;
		AmmoInClip = WeaponConfig.AmmoPerClip;
	}
}

void AShootingWeapon::SetTriggerReady()
{
	bTriggerReady = true;
}
