// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "HungryHeroKnifeAttackComponent.generated.h"

class UStaticMeshComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUNGRYHERO_API UHungryHeroKnifeAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 단발 칼 공격의 시각 확인용 컴포넌트 기본값을 만든다.
	UHungryHeroKnifeAttackComponent();

	// 공격 표시를 짧게 켜서 입력이 처리됐음을 보여준다.
	void StartAttack();

protected:
	// 소유 Actor에 공격 표시용 메시를 붙인다.
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Attack")
	TObjectPtr<UStaticMeshComponent> AttackVisualMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackVisibleTime = 0.18f;

	FTimerHandle AttackVisibleTimerHandle;

	// 공격 표시용 메시를 생성하고 기본 위치를 잡는다.
	void CreateAttackVisualMesh();

	// 공격 표시를 다시 숨긴다.
	void HideAttackVisual();
};
