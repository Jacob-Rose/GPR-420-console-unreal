// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
//#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "WeatherHttpActor.generated.h"

UCLASS()
class FPSGAME_API AWeatherHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeatherHttpActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Default is Burlington, VT
	float m_Latitude = 44.4792832f;
	float m_Longitude = -73.1971584f;

	FHttpModule* HttpModule;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SendWeatherRequest();

	void WeatherRequestRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void WeatherForcastRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
