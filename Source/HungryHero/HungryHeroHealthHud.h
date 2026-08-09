// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HungryHeroHealthHud.generated.h"

class UHungryHeroHealthComponent;
class UHungryHeroKnifeAttackComponent;
class UHungryHeroScoreComponent;

UCLASS()
class HUNGRYHERO_API AHungryHeroHealthHud : public AHUD
{
	GENERATED_BODY()

public:
	// 체력바와 게임오버 문구를 화면에 그린다.
	virtual void DrawHUD() override;

private:
	// 현재 플레이어의 체력 컴포넌트를 찾는다.
	UHungryHeroHealthComponent* FindPlayerHealthComponent() const;

	// 현재 플레이어의 점수 컴포넌트를 찾는다.
	UHungryHeroScoreComponent* FindPlayerScoreComponent() const;

	// 현재 플레이어의 칼 공격 컴포넌트를 찾는다.
	UHungryHeroKnifeAttackComponent* FindPlayerKnifeAttackComponent() const;

	// 체력바 배경과 현재 체력 비율을 그린다.
	void DrawHealthBar(const UHungryHeroHealthComponent* HealthComponent);

	// 현재 점수를 화면에 그린다.
	void DrawScoreText(const UHungryHeroScoreComponent* ScoreComponent);

	// 자동 공격 쿨타임 상태를 화면에 그린다.
	void DrawAttackCooldown(const UHungryHeroKnifeAttackComponent* KnifeAttackComponent);

	// 게임오버 상태일 때 화면 중앙 문구를 그린다.
	void DrawGameOverText();
};
