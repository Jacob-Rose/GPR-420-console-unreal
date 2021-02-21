// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallExplodingCube.h"

// Sets default values
ASmallExplodingCube::ASmallExplodingCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASmallExplodingCube::BeginPlay()
{
	Super::BeginPlay();

	m_MeshComp = (UStaticMeshComponent*)GetComponentByClass(UStaticMeshComponent::StaticClass()); //used for collision

	if (m_MeshComp != NULL)
	{
		m_MeshComp->OnComponentHit.AddDynamic(this, &ASmallExplodingCube::OnComponentHit);
		//we now know its not null, never change m_MeshComp now
	}
}

void ASmallExplodingCube::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (m_MeshComp != NULL)
	{
		m_MeshComp->OnComponentHit.RemoveDynamic(this, &ASmallExplodingCube::OnComponentHit);
		m_MeshComp = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ASmallExplodingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASmallExplodingCube::BeginDestroy()
{
	if (m_MeshComp != NULL)
	{
		m_MeshComp->OnComponentHit.RemoveDynamic(this, &ASmallExplodingCube::OnComponentHit);
		m_MeshComp = nullptr;
	}
	Super::BeginDestroy();
	//create explosion
}

void ASmallExplodingCube::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(m_ProjectileToReact))
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Cyan, TEXT("Bomb Spawned from Small Cube"));
		ABombActor* bomb = GetWorld()->SpawnActor<ABombActor>(m_BombToSpawn);
		bomb->m_ExplodeDelay = 0.1f;
		Destroy();
	}
	
}

