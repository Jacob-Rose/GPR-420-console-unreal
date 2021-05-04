// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BallPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT3_API ABallPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	float levelTimer = 0.0f;

	bool hasStarted = false;


	UFUNCTION(BlueprintCallable)
	void StartTimer();

	virtual void Tick(float DeltaTime) override;
};
