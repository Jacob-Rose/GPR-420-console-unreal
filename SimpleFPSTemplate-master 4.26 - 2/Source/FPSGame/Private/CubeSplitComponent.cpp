// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSplitComponent.h"

#include <Components/BoxComponent.h>

// Sets default values for this component's properties
UCubeSplitComponent::UCubeSplitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCubeSplitComponent::BeginPlay()
{
	Super::BeginPlay();

	m_MeshComp->OnComponentHit.AddDynamic(this, &UCubeSplitComponent::OnComponentHit);
	//boxComp->OnComponentHit.AddDynamic(this, &UCubeSplitComponent::OnComponentHit);
	
	
}


// Called every frame
void UCubeSplitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCubeSplitComponent::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{


}

