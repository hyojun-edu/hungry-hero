// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HungryHeroGameMode.generated.h"

UCLASS()
class HUNGRYHERO_API AHungryHeroGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// HungryHero의 기본 게임 규칙을 준비한다.
	AHungryHeroGameMode();
};
