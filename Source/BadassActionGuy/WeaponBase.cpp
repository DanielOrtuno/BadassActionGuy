// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

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

void AWeaponBase::OnEquip(ACharacter * NewOwner)
{
	if (NewOwner)
	{
		CurrentOwner = NewOwner;
		AttachToCurrentOwner();
	}
}

void AWeaponBase::OnUnequip()
{
	if (CurrentOwner)
	{
		DetachFromCurrentOwner();
		CurrentOwner = false;
	}
}

void AWeaponBase::OnThrow()
{
	// TODO: Add throwing functionality
}

ACharacter* AWeaponBase::GetCurrentOwner() const
{
	return CurrentOwner;
}

void AWeaponBase::AttachToCurrentOwner()
{
	if (CurrentOwner)
	{
		USkeletalMeshComponent* CurrentOwnerMesh = CurrentOwner->GetMesh();

		WeaponMesh->AttachToComponent(CurrentOwnerMesh, FAttachmentTransformRules::KeepRelativeTransform, AttachPointName);
		WeaponMesh->SetHiddenInGame(false);
	}
}

void AWeaponBase::DetachFromCurrentOwner()
{
	if (CurrentOwner)
	{
		WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}
}
