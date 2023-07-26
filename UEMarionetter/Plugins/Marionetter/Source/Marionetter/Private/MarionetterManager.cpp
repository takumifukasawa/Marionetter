// Fill out your copyright notice in the Description page of Project Settings.

#include "MarionetterManager.h"

// Sets default values
AMarionetterManager::AMarionetterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMarionetterManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMarionetterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
