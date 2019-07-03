// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class AJuanTestCharacter;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Basic,
	SmallMelee,
	LargeMelee,
	HandGun,
	LargeGun,
	HugeGun
};

UCLASS()
class BADASSACTIONGUY_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** The character has requested to equip the weapon */
	void OnEquip(AJuanTestCharacter* NewOwner);

	/** The character has requested to unequip the weapon */
	void OnUnequip();

	/** The character has requested to fire the weapon. Will only display a 'Missing' message if not overriden */
	virtual void OnStartFire();

	/** The character has requested to stop firing the weapon. Will only display a 'Missing' message if not overriden */
	virtual void OnStopFire();

	/** The character has requested to throw the weapon */
	virtual void OnThrow();

	/** Returns the current owner. Can be null */
	AJuanTestCharacter* GetCurrentOwner() const;

private:
	/** Attaches the weapon to the owner character */
	void AttachToCurrentOwner();

	/** Detaches the weapon from the character */
	void DetachFromCurrentOwner();

protected:
	/** The mesh of the weapon */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* WeaponMesh;

private:
	/** The speed at which weapons are thrown. Changing this value affects all weapons*/
	static float ThrowDistance;

	/** The type of the weapon */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	EWeaponType WeaponType;

	/** The current weapon holder */
	AJuanTestCharacter* CurrentOwner;

	/** The base damage that will be dealt if hit with this weapon when thrown */
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	float ThrownDamage;

};
