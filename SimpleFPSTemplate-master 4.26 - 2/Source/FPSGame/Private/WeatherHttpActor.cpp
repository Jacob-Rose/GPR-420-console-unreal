// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherHttpActor.h"

// Sets default values
AWeatherHttpActor::AWeatherHttpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HttpModule = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AWeatherHttpActor::BeginPlay()
{
	Super::BeginPlay();
	SendWeatherRequest();
}

// Called every frame
void AWeatherHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeatherHttpActor::SendWeatherRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	HttpRequest->SetURL("https://api.weather.gov/points/" + FString::SanitizeFloat(m_Latitude) + "," + FString::SanitizeFloat(m_Longitude));
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AWeatherHttpActor::WeatherRequestRecieved);
	HttpRequest->ProcessRequest();
}

void AWeatherHttpActor::WeatherRequestRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		//https://api.weather.gov/points/44.4793,-73.1972 example
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			TSharedPtr<FJsonObject> val = JsonObject->GetObjectField("properties");
			FString forecastLink = val->GetStringField("forecast");
			TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule->CreateRequest();
			HttpRequest->SetVerb("GET");
			HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
			HttpRequest->SetURL(forecastLink);
			HttpRequest->OnProcessRequestComplete().BindUObject(this, &AWeatherHttpActor::WeatherForcastRecieved);
			HttpRequest->ProcessRequest();
		}
	}
}

void AWeatherHttpActor::WeatherForcastRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			TSharedPtr<FJsonObject> properties = JsonObject->GetObjectField("properties");
			TArray<TSharedPtr<FJsonValue>> periods = properties->GetArrayField("periods");
			//https://api.weather.gov/gridpoints/BTV/88,56/forecast example
			//Actual useful data example
			FString shortForecast = periods[0]->AsObject()->GetStringField("shortForecast"); //Partly Cloudy, Cloudy, Sunny, Rain

		}
	}
}

