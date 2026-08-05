// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroScoreComponent.h"

UHungryHeroScoreComponent::UHungryHeroScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UHungryHeroScoreComponent::GetCurrentScore() const
{
	return CurrentScore;
}

void UHungryHeroScoreComponent::AddFoodScore()
{
	if (FoodScoreValue <= 0)
	{
		return;
	}

	CurrentScore += FoodScoreValue;
}
