// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungryHeroScoreComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUNGRYHERO_API UHungryHeroScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 플레이어 점수 기본값을 준비한다.
	UHungryHeroScoreComponent();

	// 현재 점수 값을 반환한다.
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetCurrentScore() const;

	// 음식 획득 점수를 더한다.
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddFoodScore();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Score")
	int32 FoodScoreValue = 100;

private:
	int32 CurrentScore = 0;
};
