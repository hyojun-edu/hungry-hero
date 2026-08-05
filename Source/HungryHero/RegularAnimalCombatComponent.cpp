// Copyright Epic Games, Inc. All Rights Reserved.

#include "RegularAnimalCombatComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "FoodPickup.h"
#include "TimerManager.h"

URegularAnimalCombatComponent::URegularAnimalCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	FoodPickupClass = AFoodPickup::StaticClass();
}

void URegularAnimalCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CacheBodyMesh();
}

void URegularAnimalCombatComponent::ApplyKnifeHit()
{
	if (bDefeated)
	{
		return;
	}

	++CurrentKnifeHits;
	ShowHitReaction();

	if (CurrentKnifeHits >= MaxKnifeHits)
	{
		DefeatOwnerAnimal();
	}
}

void URegularAnimalCombatComponent::CacheBodyMesh()
{
	AActor* Owner = GetOwner();
	BodyMesh = Owner ? Owner->FindComponentByClass<UStaticMeshComponent>() : nullptr;
}

void URegularAnimalCombatComponent::ShowHitReaction()
{
	if (!BodyMesh)
	{
		CacheBodyMesh();
	}

	if (BodyMesh)
	{
		BodyMesh->SetVisibility(false, true);
	}

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(HitReactionTimerHandle);
		World->GetTimerManager().SetTimer(
			HitReactionTimerHandle,
			this,
			&URegularAnimalCombatComponent::ClearHitReaction,
			HitReactionVisibleTime,
			false);
	}
}

void URegularAnimalCombatComponent::ClearHitReaction()
{
	if (BodyMesh && !bDefeated)
	{
		BodyMesh->SetVisibility(true, true);
	}
}

void URegularAnimalCombatComponent::DropFood()
{
	AActor* Owner = GetOwner();
	UWorld* World = GetWorld();
	if (!Owner || !World || !FoodPickupClass || FoodDropCount <= 0)
	{
		return;
	}

	const FVector OwnerLocation = Owner->GetActorLocation();
	const int32 DropCount = FMath::Max(1, FoodDropCount);
	for (int32 DropIndex = 0; DropIndex < DropCount; ++DropIndex)
	{
		const float OffsetIndex = static_cast<float>(DropIndex) - (static_cast<float>(DropCount - 1) * 0.5f);
		const FVector DropLocation = OwnerLocation + FVector(0.0f, OffsetIndex * FoodDropSpacing, FoodDropHeight);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		World->SpawnActor<AFoodPickup>(FoodPickupClass, DropLocation, FRotator::ZeroRotator, SpawnParameters);
	}
}

void URegularAnimalCombatComponent::DefeatOwnerAnimal()
{
	AActor* Owner = GetOwner();
	if (!Owner || bDefeated)
	{
		return;
	}

	bDefeated = true;

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(HitReactionTimerHandle);
	}

	DropFood();
	Owner->Destroy();
}
