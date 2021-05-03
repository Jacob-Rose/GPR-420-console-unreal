// Fill out your copyright notice in the Description page of Project Settings.


#include "MiscFunctionLibrary.h"


void UMiscFunctionLibrary::ChangeLevel(UObject* WorldContext, int LevelIndex)
{
	FString newLevel = "Level_";
	int nextLevel = ++LevelIndex;
	
	switch (LevelIndex)
	{
	case 1:	//In Level 1
	{
		newLevel.AppendInt(nextLevel);
		UGameplayStatics::OpenLevel(WorldContext->GetWorld(), (FName)newLevel);
		break;
	}
	case 2:	//In Level 2
	{
		newLevel.AppendInt(nextLevel);
		UGameplayStatics::OpenLevel(WorldContext->GetWorld(), (FName)newLevel);
		break;
	}
	case 3:	//In Level 3
	{
		newLevel = "MainMenu";
		UGameplayStatics::OpenLevel(WorldContext->GetWorld(), (FName)newLevel);
		break;
	}
	default:
		break;
	}
}