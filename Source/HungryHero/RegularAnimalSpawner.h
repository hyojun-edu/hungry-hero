// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "RegularAnimalSpawner.generated.h"

class ARegularAnimal;

UCLASS(Blueprintable)
class HUNGRYHERO_API ARegularAnimalSpawner : public AActor
{
	GENERATED_BODY()

public:
	// 방 가장자리 근처에서 일반 동물을 반복 생성하는 스포너를 준비한다.
	ARegularAnimalSpawner();

protected:
	// 반복 스폰 타이머를 시작한다.
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	TSubclassOf<ARegularAnimal> RegularAnimalClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	int32 MaxLiveAnimals = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float SpawnedAnimalLifeSpan = 18.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float RoomHalfExtent = 520.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float EdgeInset = 35.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float SpawnHeight = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float MinAnimalSpawnDistance = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	int32 MaxSpawnLocationAttempts = 12;

private:
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	TArray<TObjectPtr<ARegularAnimal>> SpawnedAnimals;

	// 현재 살아 있는 동물 수가 제한보다 적으면 한 마리를 생성한다.
	void SpawnRegularAnimal();

	// 파괴된 동물 참조를 목록에서 제거한다.
	void RemoveInvalidAnimals();

	// 방 네 변 중 한 곳의 가장자리 근처 위치를 고른다.
	FVector GetRandomEdgeSpawnLocation() const;

	// 후보 위치가 기존 일반 동물과 충분히 떨어져 있는지 확인한다.
	bool IsSpawnLocationSeparated(const FVector& CandidateLocation) const;

	// 플레이어가 게임오버 상태라 새 스폰을 막아야 하는지 확인한다.
	bool IsPlayerGameOver() const;
};
