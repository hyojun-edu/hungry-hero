// Copyright Epic Games, Inc. All Rights Reserved.

#include "RegularAnimalSpawner.h"

#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Pawn.h"
#include "HungryHeroHealthComponent.h"
#include "Kismet/GameplayStatics.h"
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

	if (IsPlayerGameOver() || !RegularAnimalClass || SpawnedAnimals.Num() >= MaxLiveAnimals)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	FVector SpawnLocation = FVector::ZeroVector;
	bool bFoundSeparatedSpawnLocation = false;
	const int32 SpawnAttempts = FMath::Max(1, MaxSpawnLocationAttempts);
	for (int32 AttemptIndex = 0; AttemptIndex < SpawnAttempts; ++AttemptIndex)
	{
		const FVector CandidateLocation = GetRandomEdgeSpawnLocation();
		if (IsSpawnLocationSeparated(CandidateLocation))
		{
			SpawnLocation = CandidateLocation;
			bFoundSeparatedSpawnLocation = true;
			break;
		}
	}

	if (!bFoundSeparatedSpawnLocation)
	{
		return;
	}

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

bool ARegularAnimalSpawner::IsSpawnLocationSeparated(const FVector& CandidateLocation) const
{
	UWorld* World = GetWorld();
	if (!World || MinAnimalSpawnDistance <= 0.0f)
	{
		return true;
	}

	const float MinDistanceSquared = FMath::Square(MinAnimalSpawnDistance);
	for (TActorIterator<ARegularAnimal> AnimalIterator(World); AnimalIterator; ++AnimalIterator)
	{
		const ARegularAnimal* ExistingAnimal = *AnimalIterator;
		if (!IsValid(ExistingAnimal))
		{
			continue;
		}

		if (FVector::DistSquared2D(CandidateLocation, ExistingAnimal->GetActorLocation()) < MinDistanceSquared)
		{
			return false;
		}
	}

	return true;
}

bool ARegularAnimalSpawner::IsPlayerGameOver() const
{
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn)
	{
		return false;
	}

	const UHungryHeroHealthComponent* HealthComponent = PlayerPawn->FindComponentByClass<UHungryHeroHealthComponent>();
	return HealthComponent && HealthComponent->IsGameOver();
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
