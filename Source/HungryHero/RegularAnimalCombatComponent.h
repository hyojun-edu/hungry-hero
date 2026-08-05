// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "RegularAnimalCombatComponent.generated.h"

class AFoodPickup;
class UStaticMeshComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUNGRYHERO_API URegularAnimalCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 일반 동물의 피격, 처치, 음식 드롭 상태를 준비한다.
	URegularAnimalCombatComponent();

	// 칼 공격 1회를 일반 동물에게 적용하고 공격자 반대 방향으로 밀어낸다.
	void ApplyKnifeHit(const FVector& HitSourceLocation);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Combat")
	int32 MaxKnifeHits = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Combat")
	float HitReactionVisibleTime = 0.12f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Combat")
	float KnockbackDistance = 85.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Food")
	TSubclassOf<AFoodPickup> FoodPickupClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Food")
	int32 FoodDropCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Food")
	float FoodDropSpacing = 42.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Food")
	float FoodDropHeight = 28.0f;

private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	int32 CurrentKnifeHits = 0;

	FTimerHandle HitReactionTimerHandle;

	bool bDefeated = false;

	// 소유 동물의 표시 메시를 찾아 피격 반응에 사용한다.
	void CacheBodyMesh();

	// 짧은 피격 반응을 표시한다.
	void ShowHitReaction();

	// 공격자 반대 방향으로 짧게 밀어 타격감을 만든다.
	void ApplyKnockback(const FVector& HitSourceLocation);

	// 피격 반응 표시를 기본 상태로 되돌린다.
	void ClearHitReaction();

	// 처치 위치 주변에 음식 액터를 남긴다.
	void DropFood();

	// 필요한 타격 횟수에 도달했을 때 동물을 제거한다.
	void DefeatOwnerAnimal();
};
