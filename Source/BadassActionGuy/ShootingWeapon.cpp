// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"

AShootingWeapon::AShootingWeapon()
{

}

void AShootingWeapon::Fire()
{
	const USkeletalMeshSocket* MuzzleSocket;
	MuzzleSocket = WeaponMesh->GetSocketByName(Muzzle);

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(Projectile, 
		MuzzleSocket->GetSocketTransform(WeaponMesh), FActorSpawnParameters());

	USkeletalMeshComponent* ProjectileMesh = Cast<USkeletalMeshComponent>
		(SpawnedProjectile->GetRootComponent());

	ProjectileMesh->AddImpulse(MuzzleSocket->GetSocketTransform(WeaponMesh).GetScaledAxis(EAxis::X)
		* 100);

	UE_LOG(LogTemp, Warning, TEXT("AShootingWeapon::Fire"));
}
