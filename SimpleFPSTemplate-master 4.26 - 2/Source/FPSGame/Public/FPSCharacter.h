// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CubeSplitComponent.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class AFPSProjectile;
class USoundBase;
class UAnimSequence;



UCLASS()
class AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/** Pawn mesh: 1st person view  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* Mesh1PComponent;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* GunMeshComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Charging")
	bool bIsCharging = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Charging")
	bool bCooldown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Charging")
	float MaxCharge = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Charging")
	float CurrentCharge = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Charging")
	float CooldownTimer = 0.0f;

	const float TIME_TO_COOLDOWN = 3.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box Setup")
	TArray<AActor*> BoxArray;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AFPSCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "Box Setup")
	TSubclassOf<UActorComponent> CubeSplitClass;
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<AFPSProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	UAnimSequence* FireAnimation;

protected:
		
	/** Fires a projectile. */
	void Fire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/** Charges projectile AOE when shift hit */
	void ChargePress();

	void ChargeRelease();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1PComponent; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

};

