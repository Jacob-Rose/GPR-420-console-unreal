// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MiscFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT3_API UMiscFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void ChangeLevel(UObject* WorldContext, int LevelIndex);
};
