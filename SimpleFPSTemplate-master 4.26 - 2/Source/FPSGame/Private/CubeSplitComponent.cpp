// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSplitComponent.h"

#include <Components/BoxComponent.h>
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UCubeSplitComponent::UCubeSplitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Content/Blueprints/BP_Bomb")); //we loaded the bomb in c++, a blueprint
	// ...
}


// Called when the game starts
void UCubeSplitComponent::BeginPlay()
{
	Super::BeginPlay();
	m_MeshComp = (UStaticMeshComponent*)GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()); //used for collision

	if (m_MeshComp != NULL)
	{
		m_MeshComp->OnComponentHit.AddDynamic(this, &UCubeSplitComponent::OnComponentHit);
	}
	
}

void UCubeSplitComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (m_MeshComp != NULL)
	{
		m_MeshComp->OnComponentHit.RemoveDynamic(this, &UCubeSplitComponent::OnComponentHit);
		m_MeshComp = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UCubeSplitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCubeSplitComponent::OnComponentDestroyed(bool bDestroyHierarchy)
{
	if (m_MeshComp != NULL)
	{
		m_MeshComp->OnComponentHit.RemoveDynamic(this, &UCubeSplitComponent::OnComponentHit);
		m_MeshComp = nullptr;
	}
	Super::OnComponentDestroyed(bDestroyHierarchy);
}

void UCubeSplitComponent::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(m_ProjectileToReact))
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Cyan, TEXT("Hit"));
		FActorSpawnParameters spawnParams;
		FVector loc = GetOwner()->GetActorLocation();
		FRotator rot = GetOwner()->GetActorRotation();
		loc += FVector(150.0f, 150.0f, 300.0f);
		AActor* actor = GetWorld()->SpawnActor<AActor>(m_SplitCubeTemplate.Get(), loc, rot, spawnParams);
		//actor->AddComponent("CubeSplitComponent",false, actor->GetActorTransform(),GetWorld());
		loc += FVector(-300.0f, 0.0f, 0.0f);
		actor->SetActorScale3D(GetOwner()->GetActorScale3D() * 0.25f);
		actor = GetWorld()->SpawnActor<AActor>(m_SplitCubeTemplate.Get(), loc, rot, spawnParams);
		//actor->AddComponent("CubeSplitComponent", false, actor->GetActorTransform(), GetWorld());
		loc += FVector(0.0f, -300.0f, 0.0f);
		actor->SetActorScale3D(GetOwner()->GetActorScale3D() * 0.25f);
		actor = GetWorld()->SpawnActor<AActor>(m_SplitCubeTemplate.Get(), loc, rot, spawnParams);
		//actor->AddComponent("CubeSplitComponent", false, actor->GetActorTransform(), GetWorld());
		actor->SetActorScale3D(GetOwner()->GetActorScale3D() * 0.25f);
		loc += FVector(300.0f, 0.0f, 0.0f);
		actor = GetWorld()->SpawnActor<AActor>(m_SplitCubeTemplate.Get(), loc, rot, spawnParams);
		//actor->AddComponent("CubeSplitComponent", false, actor->GetActorTransform(), GetWorld());
		actor->SetActorScale3D(GetOwner()->GetActorScale3D() * 0.25f);
		GetOwner()->Destroy();
	}

}
