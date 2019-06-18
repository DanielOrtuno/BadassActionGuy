// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomaticShootingWeapon.h"
#include "Components/Button.h"
#include "Public/TimerManager.h"

AAutomaticShootingWeapon::AAutomaticShootingWeapon()
{

}

void AAutomaticShootingWeapon::Tick(float DeltaTime)
{
}

void AAutomaticShootingWeapon::OnStartFire()
{
	GetWorldTimerManager().SetTimer(FireHandle, this, &AAutomaticShootingWeapon::Fire, AutomaticWeaponConfig.TimeBetweenShots, true, 0.0f);
	UE_LOG(LogTemp, Warning, TEXT("AAutomaticShootingWeapon::OnStartFire"));
}

void AAutomaticShootingWeapon::OnStopFire()
{
	GetWorldTimerManager().ClearTimer(FireHandle);
	UE_LOG(LogTemp, Warning, TEXT("AAutomaticShootingWeapon::OnStopFire"));
}
