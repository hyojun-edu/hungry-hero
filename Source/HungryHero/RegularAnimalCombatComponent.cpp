// Copyright Epic Games, Inc. All Rights Reserved.

#include "RegularAnimalCombatComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "FoodPickup.h"
#include "GameFramework/Actor.h"
#include "RegularAnimal.h"
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

void URegularAnimalCombatComponent::ApplyKnifeHit(const FVector& HitSourceLocation)
{
	if (bDefeated)
	{
		return;
	}

	++CurrentKnifeHits;
	if (ARegularAnimal* OwnerAnimal = Cast<ARegularAnimal>(GetOwner()))
	{
		OwnerAnimal->StunForKnifeHit();
	}

	ShowHitReaction();
	ApplyKnockback(HitSourceLocation);

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

void URegularAnimalCombatComponent::ApplyKnockback(const FVector& HitSourceLocation)
{
	AActor* Owner = GetOwner();
	if (!Owner || KnockbackDistance <= 0.0f)
	{
		return;
	}

	FVector KnockbackDirection = Owner->GetActorLocation() - HitSourceLocation;
	KnockbackDirection.Z = 0.0f;
	KnockbackDirection.Normalize();
	if (KnockbackDirection.IsNearlyZero())
	{
		KnockbackDirection = -Owner->GetActorForwardVector().GetSafeNormal2D();
	}

	FHitResult HitResult;
	Owner->AddActorWorldOffset(KnockbackDirection * KnockbackDistance, true, &HitResult);
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
