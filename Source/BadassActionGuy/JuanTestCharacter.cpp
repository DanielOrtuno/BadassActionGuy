// Fill out your copyright notice in the Description page of Project Settings.


#include "JuanTestCharacter.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AJuanTestCharacter::AJuanTestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJuanTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJuanTestCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EquipDefaultWeapon();
}

// Called every frame
void AJuanTestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AJuanTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJuanTestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJuanTestCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AJuanTestCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AJuanTestCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AJuanTestCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AJuanTestCharacter::StopFire);

	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &AJuanTestCharacter::ThrowWeapon);
}

void AJuanTestCharacter::MoveForward(float Value)
{
	const FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AJuanTestCharacter::MoveRight(float Value)
{
	const FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

FName AJuanTestCharacter::GetAttachPointName() const
{
	return AttachPointName;
}

bool AJuanTestCharacter::HasWeapon() const
{
	return CurrentWeapon != nullptr;
}

void AJuanTestCharacter::EquipDefaultWeapon()
{
	if (DefaultWeapon)
	{
		EquipWeapon(GetWorld()->SpawnActor<AWeaponBase>(DefaultWeapon));
	}
}

void AJuanTestCharacter::EquipWeapon(AWeaponBase * NewWeapon)
{
	if (!CurrentWeapon)
	{
		CurrentWeapon = NewWeapon;
		CurrentWeapon->OnEquip(this);
	}
}

void AJuanTestCharacter::ThrowWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->OnThrow();
		CurrentWeapon = nullptr;
	}
}

void AJuanTestCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->OnStartFire();
	}
}

void AJuanTestCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->OnStopFire();
	}
}
