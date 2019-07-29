// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Public/TimerManager.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

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

		const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		const FVector TraceStart = CameraManager->GetCameraLocation();
		const FVector TraceEnd = TraceStart + FRotationMatrix(CameraManager->GetCameraRotation()).GetScaledAxis(EAxis::X) * WeaponConfig.Range;

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredActor((AActor*)CurrentOwner);

		FHitResult HitResult;
		const bool bHasHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, TraceParams);

		const FVector ProjectileLookAt = bHasHit ? HitResult.Location : TraceEnd;

		const FVector ProjectileSpawnLocation = MuzzleSocket->GetSocketLocation(WeaponMesh);
		const FRotator ProjectileSpawnRotation = (ProjectileLookAt - ProjectileSpawnLocation).Rotation();

		GetWorld()->SpawnActor<AActor>(Projectile, ProjectileSpawnLocation, ProjectileSpawnRotation);

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
