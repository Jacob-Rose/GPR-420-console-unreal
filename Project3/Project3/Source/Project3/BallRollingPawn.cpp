// Fill out your copyright notice in the Description page of Project Settings.


#include "BallRollingPawn.h"

#include <Engine/World.h>



// Sets default values
ABallRollingPawn::ABallRollingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallRollingPawn::BeginPlay()
{
	Super::BeginPlay();
	m_CamManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
}

// Called every frame
void ABallRollingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ABallRollingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &ABallRollingPawn::MoveXUpdated);
	PlayerInputComponent->BindAxis("MoveY", this, &ABallRollingPawn::MoveXUpdated);

}

