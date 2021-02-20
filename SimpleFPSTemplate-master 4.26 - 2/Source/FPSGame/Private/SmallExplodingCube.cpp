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
	//AddComponentByClass(meshCompToAdd, false, GetTransform(), false);
	//GetComponentByClass<UStaticMeshComponent>()->OnComponentHit.AddDynamic(this, &UCubeSplitComponent::OnComponentHit);
}

// Called every frame
void ASmallExplodingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASmallExplodingCube::BeginDestroy()
{
	Super::BeginDestroy();
	//create explosion
}

void ASmallExplodingCube::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

