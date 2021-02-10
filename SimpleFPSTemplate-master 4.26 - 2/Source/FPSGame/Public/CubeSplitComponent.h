// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CubeSplitComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UCubeSplitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCubeSplitComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* boxComp;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//https://unrealcpp.com/on-component-hit/
	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
