// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungryHeroKnifeAttackComponent.generated.h"

class ARegularAnimal;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUNGRYHERO_API UHungryHeroKnifeAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 단발 칼 공격의 시각 확인용 컴포넌트 기본값을 만든다.
	UHungryHeroKnifeAttackComponent();

	// 칼 공격 후보를 판정하고 공격 범위를 짧게 표시한다.
	void StartAttack();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackRange = 220.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackHalfAngleDegrees = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackDebugVisibleTime = 0.18f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	int32 AttackDebugSegmentCount = 12;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackDebugHeight = 8.0f;

	// 칼 공격 범위 안에 들어온 일반 동물 후보를 찾는다.
	TArray<ARegularAnimal*> FindAttackCandidates() const;

	// 대상 Actor가 현재 칼 공격 부채꼴 안에 있는지 확인한다.
	bool IsActorInAttackCone(const AActor* TargetActor) const;

	// 플레이 중 확인할 수 있도록 부채꼴 공격 범위를 선으로 표시한다.
	void DrawAttackConeDebug(const TArray<ARegularAnimal*>& AttackCandidates) const;
};
