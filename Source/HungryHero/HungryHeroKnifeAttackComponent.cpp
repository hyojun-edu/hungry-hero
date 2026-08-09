// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroKnifeAttackComponent.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "HungryHeroHealthComponent.h"
#include "RegularAnimal.h"

UHungryHeroKnifeAttackComponent::UHungryHeroKnifeAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHungryHeroKnifeAttackComponent::UpdateAutoAttack(float DeltaTime)
{
	if (IsOwnerGameOver())
	{
		return;
	}

	AttackCooldownRemaining = FMath::Max(0.0f, AttackCooldownRemaining - DeltaTime);

	if (AttackCooldownRemaining <= 0.0f && HasAttackCandidate())
	{
		StartAttack();
	}
}

bool UHungryHeroKnifeAttackComponent::StartAttack()
{
	if (AttackCooldownRemaining > 0.0f || IsOwnerGameOver())
	{
		return false;
	}

	const TArray<ARegularAnimal*> AttackCandidates = FindAttackCandidates();
	if (AttackCandidates.IsEmpty())
	{
		return false;
	}

	DrawAttackConeDebug(AttackCandidates);

	const AActor* Owner = GetOwner();
	const FVector AttackSourceLocation = Owner ? Owner->GetActorLocation() : FVector::ZeroVector;
	for (ARegularAnimal* AttackCandidate : AttackCandidates)
	{
		if (IsValid(AttackCandidate))
		{
			AttackCandidate->ApplyKnifeHit(AttackSourceLocation);
		}
	}

	AttackCooldownRemaining = FMath::Max(AttackCooldownDuration, 0.0f);
	return true;
}

float UHungryHeroKnifeAttackComponent::GetAttackCooldownRemaining() const
{
	return AttackCooldownRemaining;
}

float UHungryHeroKnifeAttackComponent::GetAttackCooldownDuration() const
{
	return AttackCooldownDuration;
}

float UHungryHeroKnifeAttackComponent::GetAttackCooldownPercent() const
{
	if (AttackCooldownDuration <= 0.0f)
	{
		return 1.0f;
	}

	return FMath::Clamp(1.0f - (AttackCooldownRemaining / AttackCooldownDuration), 0.0f, 1.0f);
}

bool UHungryHeroKnifeAttackComponent::IsOwnerGameOver() const
{
	const AActor* Owner = GetOwner();
	if (!Owner)
	{
		return false;
	}

	const UHungryHeroHealthComponent* HealthComponent = Owner->FindComponentByClass<UHungryHeroHealthComponent>();
	return HealthComponent && HealthComponent->IsGameOver();
}

TArray<ARegularAnimal*> UHungryHeroKnifeAttackComponent::FindAttackCandidates() const
{
	TArray<ARegularAnimal*> AttackCandidates;

	UWorld* World = GetWorld();
	if (!World)
	{
		return AttackCandidates;
	}

	for (TActorIterator<ARegularAnimal> AnimalIterator(World); AnimalIterator; ++AnimalIterator)
	{
		ARegularAnimal* Animal = *AnimalIterator;
		if (IsValid(Animal) && IsActorInAttackCone(Animal))
		{
			AttackCandidates.Add(Animal);
		}
	}

	return AttackCandidates;
}

bool UHungryHeroKnifeAttackComponent::HasAttackCandidate() const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	for (TActorIterator<ARegularAnimal> AnimalIterator(World); AnimalIterator; ++AnimalIterator)
	{
		ARegularAnimal* Animal = *AnimalIterator;
		if (IsValid(Animal) && IsActorInAttackCone(Animal))
		{
			return true;
		}
	}

	return false;
}

bool UHungryHeroKnifeAttackComponent::IsActorInAttackCone(const AActor* TargetActor) const
{
	const AActor* Owner = GetOwner();
	if (!Owner || !TargetActor || AttackRange <= 0.0f)
	{
		return false;
	}

	FVector ToTarget = TargetActor->GetActorLocation() - Owner->GetActorLocation();
	ToTarget.Z = 0.0f;

	const float Distance = ToTarget.Size();
	if (Distance <= 0.0f || Distance > AttackRange)
	{
		return false;
	}

	FVector Forward = Owner->GetActorForwardVector();
	Forward.Z = 0.0f;
	Forward.Normalize();

	const FVector DirectionToTarget = ToTarget / Distance;
	const float Dot = FVector::DotProduct(Forward, DirectionToTarget);
	const float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(FMath::Clamp(Dot, -1.0f, 1.0f)));
	return AngleDegrees <= AttackHalfAngleDegrees;
}

void UHungryHeroKnifeAttackComponent::DrawAttackConeDebug(const TArray<ARegularAnimal*>& AttackCandidates) const
{
	const AActor* Owner = GetOwner();
	UWorld* World = GetWorld();
	if (!Owner || !World || AttackRange <= 0.0f)
	{
		return;
	}

	const int32 SegmentCount = FMath::Max(AttackDebugSegmentCount, 2);
	const FVector Origin = Owner->GetActorLocation() + FVector(0.0f, 0.0f, AttackDebugHeight);
	const FVector Forward = Owner->GetActorForwardVector().GetSafeNormal2D();
	const FColor ConeColor = FColor::Yellow;
	const FColor CandidateColor = FColor::Green;

	FVector PreviousPoint = FVector::ZeroVector;
	for (int32 SegmentIndex = 0; SegmentIndex <= SegmentCount; ++SegmentIndex)
	{
		const float SegmentAlpha = static_cast<float>(SegmentIndex) / static_cast<float>(SegmentCount);
		const float AngleDegrees = FMath::Lerp(-AttackHalfAngleDegrees, AttackHalfAngleDegrees, SegmentAlpha);
		const FVector SegmentDirection = Forward.RotateAngleAxis(AngleDegrees, FVector::UpVector);
		const FVector SegmentPoint = Origin + SegmentDirection * AttackRange;

		DrawDebugLine(World, Origin, SegmentPoint, ConeColor, false, AttackDebugVisibleTime, 0, 2.0f);

		if (SegmentIndex > 0)
		{
			DrawDebugLine(World, PreviousPoint, SegmentPoint, ConeColor, false, AttackDebugVisibleTime, 0, 3.0f);
		}

		PreviousPoint = SegmentPoint;
	}

	for (const ARegularAnimal* Candidate : AttackCandidates)
	{
		if (IsValid(Candidate))
		{
			const FVector CandidateLocation = Candidate->GetActorLocation() + FVector(0.0f, 0.0f, AttackDebugHeight + 18.0f);
			DrawDebugSphere(World, CandidateLocation, 38.0f, 12, CandidateColor, false, AttackDebugVisibleTime, 0, 3.0f);
		}
	}
}
