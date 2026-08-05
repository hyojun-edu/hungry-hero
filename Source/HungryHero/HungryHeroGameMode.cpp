// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroGameMode.h"

#include "HungryHeroPlayerPawn.h"

AHungryHeroGameMode::AHungryHeroGameMode()
{
	DefaultPawnClass = AHungryHeroPlayerPawn::StaticClass();
}
