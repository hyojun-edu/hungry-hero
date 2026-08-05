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

void UHungryHeroHealthComponent::ApplyDamage(float DamageAmount)
{
	ReduceHealth(DamageAmount);
}

void UHungryHeroHealthComponent::Heal(float HealAmount)
{
	if (bIsGameOver)
	{
		return;
	}

	if (HealAmount <= 0.0f || MaxHealth <= 0.0f)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
}

void UHungryHeroHealthComponent::DrainHealth(float DeltaTime)
{
	ReduceHealth(HealthDrainPerSecond * DeltaTime);
}

void UHungryHeroHealthComponent::ReduceHealth(float DamageAmount)
{
	if (bIsGameOver)
	{
		return;
	}

	if (DamageAmount <= 0.0f)
	{
		return;
	}

	CurrentHealth = FMath::Max(0.0f, CurrentHealth - DamageAmount);
	if (CurrentHealth <= 0.0f)
	{
		bIsGameOver = true;
	}
}
