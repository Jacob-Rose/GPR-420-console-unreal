// Fill out your copyright notice in the Description page of Project Settings.


#include "BombActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABombActor::ABombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ExplodeDelay = 2.0f;

}

void ABombActor::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, m_ExplosionTemplate, GetActorLocation(),GetActorRotation(),GetActorScale()*4.0f);


	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape CollShape;
	CollShape.SetSphere(m_ExplosionRadius);

	TArray<FOverlapResult> OutOverlaps;
	GetWorld()->OverlapMultiByObjectType(OutOverlaps, GetActorLocation(), FQuat::Identity, QueryParams, CollShape);

	for (FOverlapResult Result : OutOverlaps)
	{
		UPrimitiveComponent* Overlap = Result.GetComponent();
		if (Overlap && Overlap->IsSimulatingPhysics())
		{
			Overlap->AddRadialForce(GetActorLocation(), m_ExplosionRadius, m_ExplosionForce, ERadialImpulseFalloff::RIF_Linear);
		}
	}


	Destroy();
}

// Called when the game starts or when spawned
void ABombActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Explode_TimerHandle;
	GetWorldTimerManager().SetTimer(Explode_TimerHandle, this, &ABombActor::Explode, m_ExplodeDelay);
	
}

// Called every frame
void ABombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

