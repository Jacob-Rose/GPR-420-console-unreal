// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimSequence.h"


void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Get all boxes in world (I already tagged them)
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "PhysicsBox", BoxArray);

	if (CubeSplitClass)
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Cyan, TEXT("Pls"));
		for (int i = 0; i < BoxArray.Num(); i++)
		{
			//Add the cube split component to each, so we can control what happens when they get shot
			//BoxArray[i]->AddComponent("CubeSplitComponent",false, BoxArray[i]->GetActorTransform(),cubeComp)
			BoxArray[i]->AddComponentByClass(CubeSplitClass, false, BoxArray[i]->GetActorTransform(), false);
		}

	}
}

AFPSCharacter::AFPSCharacter()
{
	//Charging will need the ability to tick
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0, 0, BaseEyeHeight)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1PComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh1PComponent->SetupAttachment(CameraComponent);
	Mesh1PComponent->CastShadow = false;
	Mesh1PComponent->SetRelativeRotation(FRotator(2.0f, -15.0f, 5.0f));
	Mesh1PComponent->SetRelativeLocation(FVector(0, 0, -160.0f));

	// Create a gun mesh component
	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	GunMeshComponent->CastShadow = false;
	GunMeshComponent->SetupAttachment(Mesh1PComponent, "GripPoint");


}


void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	PlayerInputComponent->BindAction("Charge", IE_Pressed, this, &AFPSCharacter::ChargePress);
	PlayerInputComponent->BindAction("Charge", IE_Released, this, &AFPSCharacter::ChargeRelease);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsCharging && !bCooldown)
	{
		//Add deltaTime to charge variable until >= max charge
		if (CurrentCharge < MaxCharge)
		{
			CurrentCharge += DeltaTime;
		}
		else
		{
			CurrentCharge = MaxCharge;
		}
	}
	else
	{
		CurrentCharge = 0.0f;
	}
	/*
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Cyan, FString::Printf(TEXT("Charge: %i"),CurrentCharge));
	}*/

	if (bCooldown)
	{
		CooldownTimer += DeltaTime;
		if (CooldownTimer >= TIME_TO_COOLDOWN)
		{
			bCooldown = false;
			CooldownTimer = 0.0f;
		}
	}

	for (int i = 0; i < BoxArray.Num(); i++)
	{
		if (BoxArray[i] == nullptr)
		{
			BoxArray.RemoveAt(i);
		}
	}

}

void AFPSCharacter::ChargePress()
{
	/*
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Cyan, TEXT("ChargePressed"));
	}*/
	bIsCharging = true;
}

void AFPSCharacter::ChargeRelease()
{
	bIsCharging = false;
}

void AFPSCharacter::Fire()
{
	// try and fire a projectile
	if (ProjectileClass)
	{
		// Grabs location from the mesh that must have a socket called "Muzzle" in his skeleton
		FVector MuzzleLocation = GunMeshComponent->GetSocketLocation("Muzzle");
		// Use controller rotation which is our view direction in first person
		FRotator MuzzleRotation = GetControlRotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		AFPSProjectile* temp = GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParams);
		if (bIsCharging)
		{
			temp->bIsCharged = bIsCharging;
			temp->ChargeVal = CurrentCharge;
			temp->BoxArray = BoxArray;

			bCooldown = true;
		}
	}

	// try and play the sound if specified
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1PComponent->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(FireAnimation, "Arms", 0.0f);
		}
	}
}


void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}