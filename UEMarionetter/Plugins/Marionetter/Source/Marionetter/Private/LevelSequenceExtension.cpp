// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceExtension.h"

float ULevelSequenceExtension::GetSequenceActorCurrentRootTime(const ALevelSequenceActor* SequenceActor)
{
	if(!IsValid(SequenceActor)) return -1;

	const auto Player = SequenceActor->SequencePlayer;
	FLevelSequencePlayerSnapshot Snapshot;
	Player->TakeFrameSnapshot(Snapshot);
	return Snapshot.RootTime.AsSeconds();
}

float ULevelSequenceExtension::GetSequenceActorCurrentShotLocalTime(const ALevelSequenceActor* SequenceActor)
{
	if(!IsValid(SequenceActor)) return -1;

	const auto Player = SequenceActor->SequencePlayer;
	FLevelSequencePlayerSnapshot Snapshot;
	Player->TakeFrameSnapshot(Snapshot);
	return Snapshot.CurrentShotLocalTime.AsSeconds();
}


// float ULevelSequenceExtension::GetSequenceActorSnapshot(const ALevelSequenceActor* SequenceActor)
// {
// 	// if(!IsValid(SequenceActor)) return;
// 	const auto Player = SequenceActor->SequencePlayer;
// 	FLevelSequencePlayerSnapshot Snapshot;
// 	Player->TakeFrameSnapshot(Snapshot);
// 	return Snapshot;
// }
