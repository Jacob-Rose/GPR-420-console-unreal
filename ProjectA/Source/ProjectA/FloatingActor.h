// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"


UENUM()
enum Status
{
	Stopped     UMETA(DisplayName = "Stopped"),
	Moving      UMETA(DisplayName = "Moving"),
	Attacking   UMETA(DisplayName = "Attacking"),
};



UCLASS()
class PROJECTA_API AFloatingActor : public AActor
{

	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloatingActor();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	TEnumAsByte<Status> status;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};