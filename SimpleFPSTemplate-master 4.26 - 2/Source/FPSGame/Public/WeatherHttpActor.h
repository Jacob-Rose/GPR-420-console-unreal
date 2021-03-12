// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
//#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "WeatherHttpActor.generated.h"

USTRUCT(BlueprintType)
struct FWeatherPeriod
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FString name;

	UPROPERTY(BlueprintReadOnly)
	FString startTime;

	UPROPERTY(BlueprintReadOnly)
	bool isDaytime;

	UPROPERTY(BlueprintReadOnly)
	int temperature;

	UPROPERTY(BlueprintReadOnly)
	FString temperatureUnit;

	UPROPERTY(BlueprintReadOnly)
	FString shortForecast;

	UPROPERTY(BlueprintReadOnly)
	FString detailedForecast;
};

USTRUCT(BlueprintType)
struct FWeatherForecast
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FDateTime updated;

	UPROPERTY(BlueprintReadOnly)
	FString cwa; //location tag, ex. BTV

	UPROPERTY(BlueprintReadOnly)
	TArray<FWeatherPeriod> periods;
};


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

	UPROPERTY(BlueprintReadOnly)
	FWeatherForecast m_UpdatedWeatherForecast;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SendWeatherRequest();

	void WeatherRequestRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void WeatherForcastRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
