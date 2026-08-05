// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungryHeroHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUNGRYHERO_API UHungryHeroHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 플레이어 체력 기본값과 자동 감소 설정을 만든다.
	UHungryHeroHealthComponent();

	// 현재 체력 값을 반환한다.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const;

	// 최대 체력 값을 반환한다.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const;

	// 체력바 표시에 사용할 0~1 비율을 반환한다.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	// 체력이 0이 되어 게임오버 상태인지 반환한다.
	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsGameOver() const;

	// 외부 충돌이나 공격으로 체력을 감소시킨다.
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(float DamageAmount);

protected:
	// 시작 시 체력을 최대 체력으로 맞춘다.
	virtual void BeginPlay() override;

	// 음식이 없는 현재 단계에서는 매 프레임 체력을 감소시킨다.
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float HealthDrainPerSecond = 3.333333f;

private:
	float CurrentHealth = 0.0f;

	bool bIsGameOver = false;

	// 체력을 감소시키고 0에 도달하면 게임오버 상태로 바꾼다.
	void DrainHealth(float DeltaTime);

	// 체력 값을 줄이고 게임오버 상태를 갱신한다.
	void ReduceHealth(float DamageAmount);
};
