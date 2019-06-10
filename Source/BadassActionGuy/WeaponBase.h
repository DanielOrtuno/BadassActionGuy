// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Projectile,
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

private:
	/** The mesh of the weapon */
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* WeaponMesh;

private:
	/** The type of the weapon */
	UPROPERTY(EditDefaultsOnly, Category = WeaponType)
	EWeaponType WeaponType;

};