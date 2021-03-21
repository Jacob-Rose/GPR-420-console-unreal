// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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
	InitialLifeSpan = 5.0f;

}

void AFPSProjectile::DestroyBuildDestroy(AActor* HitBox, float randomNum)
{	
	for (int i = 0; i < BoxArray.Num(); i++)
	{
		if (HitBox != BoxArray[i]&& FVector::Dist(HitBox->GetActorLocation(), BoxArray[i]->GetActorLocation())<ChargeVal*100.0f)	//If the hit actor is not the box actor, and the distance between is less than the radius
		{
			float finalRand = randomNum * FMath::RandRange(1.0f, ChargeVal);
			UParticleSystemComponent* PS = UGameplayStatics::SpawnEmitterAtLocation(this, m_ExplosionTemplate, BoxArray[i]->GetActorLocation(), BoxArray[i]->GetActorRotation(), BoxArray[i]->GetActorScale3D()*finalRand);	//Gonna want to put these in a sepparate function with a timer delegate
			if (PS != nullptr)
			{
				//PS->SetWorldScale3D(FVector(finalRand));
			}
			BoxArray[i]->Destroy();
		}
	}
	UParticleSystemComponent* finalPS = UGameplayStatics::SpawnEmitterAtLocation(this, m_ExplosionTemplate, HitBox->GetActorLocation(), HitBox->GetActorRotation(), HitBox->GetActorScale3D()*(randomNum*FMath::RandRange(1.0f,ChargeVal)));
	
	//ABombActor* myBomb = GetWorld()->SpawnActor<ABombActor>(bombClass, OtherActor->GetActorLocation(), OtherActor->GetActorRotation());
	HitBox->Destroy();
	//myBomb->SetActorScale3D(myBomb->GetActorScale3D() * 2.0f * ChargeVal);
}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		if (bIsCharged)
		{
			FTimerHandle TimerHandle;
			FTimerDelegate TimerDel;
			float Random = FMath::RandRange(1.0f, 5.0f);
			TimerDel.BindUFunction(this, FName("DestroyBuildDestroy"), OtherActor, Random);
			UWorld* World = GetWorld();
			if (World != nullptr)
			{
				World->GetTimerManager().SetTimer(TimerHandle, TimerDel, 1.0f, false);	//Working now!
			}
			return;
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
			OtherComp->SetWorldScale3D(Scale);
			//Old from project, conflicts with new definition
			
			if (Scale.GetMin() < 0.8f)
			{
				ABombActor* myBomb = GetWorld()->SpawnActor<ABombActor>(bombClass, OtherActor->GetActorLocation(), OtherActor->GetActorRotation());
				OtherComp->GetOwner()->Destroy();
			}/*
			else if (Scale.GetMin() < 0.9)
			{

			}*/
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