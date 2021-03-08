// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"


class UProjectileMovementComponent;
class USphereComponent;
class ABombActor;


UCLASS()
class AFPSProjectile : public AActor
{
	GENERATED_BODY()

protected:

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Projectile")
	USphereComponent* CollisionComp;



	UPROPERTY(EditDefaultsOnly, Category = "Bomb")
	TSubclassOf<ABombActor> bombClass;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	UParticleSystem* m_ExplosionTemplate;

	//TArray<AActor*>* ArrayOfBox;	//Assign this to FPSCharacter array of exploding boxes
public:

	AFPSProjectile();

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void DestroyBuildDestroy(AActor* HitBox, float randomNum);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	/** Returns ProjectileMovement subobject **/
	//UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	bool bIsCharged = false;

	float ChargeVal = 0.0f;

	float ShotSpeed = 3000.0f;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> BoxArray;

	void SetSpeed(float newSpeed);

};

