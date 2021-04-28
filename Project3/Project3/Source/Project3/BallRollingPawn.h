// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Runtime/Engine/Classes/Camera/PlayerCameraManager.h>


#include "BallRollingPawn.generated.h" //LAST INCLUDE

UCLASS()
class PROJECT3_API ABallRollingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallRollingPawn();

	UPROPERTY(BlueprintReadWrite)
	float m_ForceAmount = 100.0f;

	UPROPERTY(BlueprintReadWrite)
	float m_JumpForce = 1000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerCameraManager* m_CamManager;
	FVector2D m_CurrentForce;

	void MoveXUpdated(float axis) { m_CurrentForce.X = axis; }
	void MoveYUpdated(float axis) { m_CurrentForce.Y = axis; }

	UFUNCTION(BlueprintCallable)
	void Jump();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
