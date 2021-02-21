// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BombActor.h"

AFPSProjectile::AFPSProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = ShotSpeed;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

}


void AFPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		if (bIsCharged)
		{
			for (int i = 0; i < BoxArray.Num(); i++)
			{
				if (OtherActor != BoxArray[i]&& FVector::Dist(OtherActor->GetActorLocation(), BoxArray[i]->GetActorLocation())<ChargeVal*100.0f)	//If the hit actor is not the box actor, and the distance between is less than the radius
				{
					BoxArray[i]->Destroy();
				}
			}
			ABombActor* myBomb = GetWorld()->SpawnActor<ABombActor>(bombClass, OtherActor->GetActorLocation(), OtherActor->GetActorRotation());
			OtherActor->Destroy();
			myBomb->SetActorScale3D(myBomb->GetActorScale3D() * 2.0f * ChargeVal);
		}
		else
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 300.0f, GetActorLocation());
		//Set Color
			UMaterialInstanceDynamic* matInstance = OtherComp->CreateAndSetMaterialInstanceDynamic(0);
			if (matInstance)
				matInstance->SetVectorParameterValue("Color", FLinearColor::MakeRandomColor());

		
		//Set Scale
			FVector Scale = OtherComp->GetComponentScale();
			Scale *= 0.8f;
			if (Scale.GetMin() < 0.8f)
			{
				//ABombActor* myBomb = GetWorld()->SpawnActor<ABombActor>(bombClass, OtherActor->GetActorLocation(), OtherActor->GetActorRotation());
				OtherComp->GetOwner()->Destroy();
			}
			else
			{
				OtherComp->SetWorldScale3D(Scale);
			}
		}
		Destroy();
	}
}

void AFPSProjectile::SetSpeed(float newSpeed)
{
	ProjectileMovement->Velocity = GetActorForwardVector().GetSafeNormal() * newSpeed;
	ProjectileMovement->ProjectileGravityScale *= 0.0f;
	SetActorScale3D(FVector(1.0f, 1.0f, 0.25f));
}