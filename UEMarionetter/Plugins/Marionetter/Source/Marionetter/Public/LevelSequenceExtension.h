// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
// #include "LevelSequence.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelSequenceExtension.generated.h"

/**
 * 
 */
UCLASS()
class MARIONETTER_API ULevelSequenceExtension : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="LevelSequenceExtension")
	static float GetSequenceActorCurrentRootTime(const ALevelSequenceActor* SequenceActor);
	UFUNCTION(BlueprintCallable, Category="LevelSequenceExtension")
	static float GetSequenceActorCurrentShotLocalTime(const ALevelSequenceActor* SequenceActor);
	// static FLevelSequencePlayerSnapshot GetSequenceActorSnapshot(const ALevelSequenceActor* SequenceActor);
};
