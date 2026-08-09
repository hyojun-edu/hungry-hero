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

	// 공격 쿨타임을 갱신하고 범위 안 일반 동물이 있으면 자동으로 공격한다.
	void UpdateAutoAttack(float DeltaTime);

	// 칼 공격 후보를 판정하고 공격 범위를 짧게 표시한다. 공격이 발동됐으면 true를 반환한다.
	bool StartAttack();

	// HUD 표시에 사용할 남은 공격 쿨타임 값을 반환한다.
	float GetAttackCooldownRemaining() const;

	// HUD 표시에 사용할 공격 쿨타임 전체 시간을 반환한다.
	float GetAttackCooldownDuration() const;

	// HUD 막대 표시에 사용할 0~1 쿨타임 진행 비율을 반환한다.
	float GetAttackCooldownPercent() const;

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

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackCooldownDuration = 1.0f;

	float AttackCooldownRemaining = 0.0f;

	// 게임오버 상태에서는 자동 공격을 멈춘다.
	bool IsOwnerGameOver() const;

	// 칼 공격 범위 안에 들어온 일반 동물 후보를 찾는다.
	TArray<ARegularAnimal*> FindAttackCandidates() const;

	// 자동 공격을 발동할 수 있는 대상이 현재 공격 범위에 있는지 확인한다.
	bool HasAttackCandidate() const;

	// 대상 Actor가 현재 칼 공격 부채꼴 안에 있는지 확인한다.
	bool IsActorInAttackCone(const AActor* TargetActor) const;

	// 플레이 중 확인할 수 있도록 부채꼴 공격 범위를 선으로 표시한다.
	void DrawAttackConeDebug(const TArray<ARegularAnimal*>& AttackCandidates) const;
};
