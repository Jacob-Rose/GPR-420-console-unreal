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
	ballMesh = dynamic_cast<UStaticMeshComponent*>(RootComponent);
	ballMesh->BodyInstance.MassScale = 3.5f;
	ballMesh->BodyInstance.MaxAngularVelocity = 800.0f;
}

// Called every frame
void ABallRollingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);/*
	//https://answers.unrealengine.com/questions/374113/addforce-to-this-pawn.html
	if (RootComponent && RootComponent->IsSimulatingPhysics())
	{
		if (UStaticMeshComponent* meshComp = dynamic_cast<UStaticMeshComponent*>(RootComponent))
		{
			FRotator rotation = GetActorRotation();
			//FVector force = rotation.RotateVector(FVector(m_CurrentForce.X, m_CurrentForce.Y, 0) * m_ForceAmount);
			FVector force = FVector(m_CurrentForce.X, m_CurrentForce.Y, 0);// *m_ForceAmount;
			force.Normalize();
			GEngine->AddOnScreenDebugMessage(1, 15.0f, FColor::Cyan, force.ToString());
			meshComp->AddImpulse(force * m_ForceAmount * DeltaTime);
			//meshComp->AddImpulse(force);
			//FRotator ballRotator = FRotator(force.X, force.Y, force.Z);			
		}
	}*/
}

void ABallRollingPawn::MoveForward(float yVal)
{
	FVector movement = FVector(0.0f, yVal * m_ForceAmount, 0.0f);
	ballMesh->AddTorqueInRadians(movement);
}

void ABallRollingPawn::MoveRight(float xVal)
{
	FVector movement = FVector(-1.0f * xVal * m_ForceAmount, 0.0f, 0.0f);
	ballMesh->AddTorqueInRadians(movement);
}

void ABallRollingPawn::TurnCamera(float value)
{
	AddControllerYawInput(value);
}

void ABallRollingPawn::LookUpCamera(float value)
{
	AddControllerPitchInput(value);
}

void ABallRollingPawn::Jump()
{
	if (RootComponent && RootComponent->IsSimulatingPhysics())
	{
		FRotator rotation = GetActorRotation();
		FVector force = FVector(0.0f,0.0f,m_JumpForce);
		ballMesh->AddForce(force);
	}
}

// Called to bind functionality to input
void ABallRollingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &ABallRollingPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveY", this, &ABallRollingPawn::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ABallRollingPawn::TurnCamera);
	PlayerInputComponent->BindAxis("LookUp", this, &ABallRollingPawn::LookUpCamera);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABallRollingPawn::Jump);
}

