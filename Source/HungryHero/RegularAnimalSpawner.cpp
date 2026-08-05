// Copyright Epic Games, Inc. All Rights Reserved.

#include "RegularAnimalSpawner.h"

#include "Engine/World.h"
#include "RegularAnimal.h"
#include "TimerManager.h"

ARegularAnimalSpawner::ARegularAnimalSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	RegularAnimalClass = ARegularAnimal::StaticClass();
}

void ARegularAnimalSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnRegularAnimal();

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&ARegularAnimalSpawner::SpawnRegularAnimal,
			SpawnInterval,
			true);
	}
}

void ARegularAnimalSpawner::SpawnRegularAnimal()
{
	RemoveInvalidAnimals();

	if (!RegularAnimalClass || SpawnedAnimals.Num() >= MaxLiveAnimals)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const FVector SpawnLocation = GetRandomEdgeSpawnLocation();
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ARegularAnimal* SpawnedAnimal = World->SpawnActor<ARegularAnimal>(
		RegularAnimalClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParameters);

	if (SpawnedAnimal)
	{
		SpawnedAnimal->SetLifeSpan(SpawnedAnimalLifeSpan);
		SpawnedAnimals.Add(SpawnedAnimal);
	}
}

void ARegularAnimalSpawner::RemoveInvalidAnimals()
{
	SpawnedAnimals.RemoveAll([](const TObjectPtr<ARegularAnimal>& Animal)
	{
		return !IsValid(Animal);
	});
}

FVector ARegularAnimalSpawner::GetRandomEdgeSpawnLocation() const
{
	const float SpawnRange = FMath::Max(0.0f, RoomHalfExtent - EdgeInset);
	const float FixedEdge = SpawnRange;
	const float RandomSidePosition = FMath::FRandRange(-SpawnRange, SpawnRange);

	switch (FMath::RandRange(0, 3))
	{
	case 0:
		return FVector(FixedEdge, RandomSidePosition, SpawnHeight);
	case 1:
		return FVector(-FixedEdge, RandomSidePosition, SpawnHeight);
	case 2:
		return FVector(RandomSidePosition, FixedEdge, SpawnHeight);
	default:
		return FVector(RandomSidePosition, -FixedEdge, SpawnHeight);
	}
}
