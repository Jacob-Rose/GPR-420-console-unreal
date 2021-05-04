// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPlayerController.h"

void ABallPlayerController::StartTimer()
{
	hasStarted = true;
	levelTimer = 0.0f;
}

void ABallPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (hasStarted)
	{
		levelTimer += DeltaTime;
	}
}
