// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroHealthComponent.h"

UHungryHeroHealthComponent::UHungryHeroHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHungryHeroHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	bIsGameOver = CurrentHealth <= 0.0f;
}

void UHungryHeroHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrainHealth(DeltaTime);
}

float UHungryHeroHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHungryHeroHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHungryHeroHealthComponent::GetHealthPercent() const
{
	if (MaxHealth <= 0.0f)
	{
		return 0.0f;
	}

	return FMath::Clamp(CurrentHealth / MaxHealth, 0.0f, 1.0f);
}

bool UHungryHeroHealthComponent::IsGameOver() const
{
	return bIsGameOver;
}

void UHungryHeroHealthComponent::DrainHealth(float DeltaTime)
{
	if (bIsGameOver)
	{
		return;
	}

	CurrentHealth = FMath::Max(0.0f, CurrentHealth - (HealthDrainPerSecond * DeltaTime));
	if (CurrentHealth <= 0.0f)
	{
		bIsGameOver = true;
	}
}
