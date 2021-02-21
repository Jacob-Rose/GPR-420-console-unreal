// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombActor.h"
#include "SmallExplodingCube.generated.h"

UCLASS()
class FPSGAME_API ASmallExplodingCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmallExplodingCube();
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* m_MeshComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> m_ProjectileToReact;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABombActor> m_BombToSpawn;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;

	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
