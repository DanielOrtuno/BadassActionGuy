	// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Engine.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpeedModifier = 1.5f;
	SlowModifier = 0.05f;
	MaxSlowMoTime = 3.0f;
	SlowMoRechargeDelay = 2.0f;
	JumpForce = 2000.0f;

	CanPlayerJump = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SlowMoTime = MaxSlowMoTime;
	SlowMoRechargeTimer = 0.0f;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 0.1F, FColor::Emerald, *FString::FromInt(OnWall));
	}

	/** If time is slowed */
	if(GetWorldSettings()->TimeDilation != 1.0f)
	{
		if(SlowMoTime > 0.0f)
		{
			SlowMoTime -= GetWorld()->GetDeltaSeconds() / SlowModifier;
			SlowMoRechargeTimer = SlowMoRechargeDelay;
			/** Instead of checking again, wait for next tick to disable SlowMo if less or equal to zero */
		}
		else
		{
			/** Player ran out of SlowMo juice. What a pity... */
			StopSlowMo();
		}
	}
	else 
	{
		/** Check if we have to wait to refill the SlowMo time */
		if(SlowMoRechargeTimer > 0.0f)
		{
			SlowMoRechargeTimer -= GetWorld()->GetDeltaSeconds();
		}
		else if(SlowMoTime < MaxSlowMoTime)
		{
			SlowMoTime = FMath::Clamp(SlowMoTime + GetWorld()->GetDeltaSeconds(), 0.0f, MaxSlowMoTime);
		}
	}


}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/** Binding movement functions */
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);

	/** Binding actions */
	//PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ABaseCharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ABaseCharacter::StopJumping);
	PlayerInputComponent->BindAction("SlowMo", EInputEvent::IE_Pressed, this, &ABaseCharacter::StartSlowMo);
	PlayerInputComponent->BindAction("SlowMo", EInputEvent::IE_Released, this, &ABaseCharacter::StopSlowMo);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ABaseCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ABaseCharacter::StopSprint);

}

void ABaseCharacter::MoveForward(float Value)
{
	//if(!OnWall)
	{
		FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	//if(!OnWall)
	{
		FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::Fire()
{
}

void ABaseCharacter::StartSlowMo()
{
	if(SlowMoTime > 0.0f)
	{
		GetWorldSettings()->SetTimeDilation(SlowModifier);
	}
}

void ABaseCharacter::StopSlowMo()
{
	GetWorldSettings()->SetTimeDilation(1.0f);
}

void ABaseCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SpeedModifier;
}

void ABaseCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= SpeedModifier;
}

