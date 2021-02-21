// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombActor.generated.h"

UCLASS()
class FPSGAME_API ABombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombActor();
	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	float m_ExplodeDelay;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	float m_ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	float m_ExplosionForce;
protected:


	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	UParticleSystem* m_ExplosionTemplate;

	UFUNCTION()
	void Explode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
