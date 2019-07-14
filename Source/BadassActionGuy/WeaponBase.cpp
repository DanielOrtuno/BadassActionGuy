// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "JuanTestCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TimerManager.h"

float AWeaponBase::ThrowDistance = 4000.f;

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	WeaponMesh->bEditableWhenInherited = true;
	RootComponent = WeaponMesh;

	WeaponType = EWeaponType::Basic;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::OnEquip(AJuanTestCharacter * NewOwner)
{
	if (NewOwner)
	{
		CurrentOwner = NewOwner;
		AttachToCurrentOwner();
		WeaponMesh->SetHiddenInGame(false);
	}
}

void AWeaponBase::OnUnequip()
{
	if (CurrentOwner)
	{
		DetachFromCurrentOwner();
		WeaponMesh->SetHiddenInGame(true);
		CurrentOwner = nullptr;
	}
}

void AWeaponBase::OnStartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Attempting to fire a base weapon / weapon without an overriden OnStartFire() method"))
}

void AWeaponBase::OnStopFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Attempting to fire a base weapon / weapon without an overriden OnStartFire() method"))
}

void AWeaponBase::OnThrow()
{
	if (CurrentOwner)
	{
		const ACharacter* ThrowingOwner = CurrentOwner;
		
		const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		const FVector StartThrowLocation = CameraManager->GetCameraLocation() + FRotationMatrix(CameraManager->GetCameraRotation()).GetScaledAxis(EAxis::X) * 100.0f;

		// This is done before detaching the weapon from the character since the DetachFromCurrentOwner activates physics simulation
		// and will mess with the SetActorLocationMethod
		// TODO: This will be edited if I figure out a better way to do this
		SetActorRelativeRotation(ThrowRotation);

		DetachFromCurrentOwner();
		SetActorLocation(StartThrowLocation, false, nullptr, ETeleportType::TeleportPhysics);

		const FVector Impulse = FRotationMatrix(ThrowingOwner->GetControlRotation()).GetScaledAxis(EAxis::X) * ThrowDistance;
		WeaponMesh->AddImpulse(Impulse, NAME_None, true);

		UE_LOG(LogTemp, Warning, TEXT("Requested to throw the weapon"))
	}
}

AJuanTestCharacter* AWeaponBase::GetCurrentOwner() const
{
	return CurrentOwner;
}

void AWeaponBase::AttachToCurrentOwner()
{
	if (CurrentOwner)
	{
		USkeletalMeshComponent* CurrentOwnerMesh = CurrentOwner->GetMesh();
		const FName AttachPointName = CurrentOwner->GetAttachPointName();

		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

		WeaponMesh->AttachToComponent(CurrentOwnerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPointName);
	}
}

void AWeaponBase::DetachFromCurrentOwner()
{
	if (CurrentOwner)
	{
		WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
		WeaponMesh->SetSimulatePhysics(true);
		
		CurrentOwner = nullptr;
	}
}