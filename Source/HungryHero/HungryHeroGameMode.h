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
	// HungryHero의 기본 플레이어 Pawn 클래스를 지정한다.
	AHungryHeroGameMode();
};
