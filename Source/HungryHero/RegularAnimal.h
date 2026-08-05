// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegularAnimal.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class URegularAnimalCombatComponent;
class APawn;

UENUM()
enum class ERegularAnimalState : uint8
{
	Approaching,
	PreparingDash,
	Dashing,
	Recovering,
	HitStunned
};

UCLASS(Blueprintable)
class HUNGRYHERO_API ARegularAnimal : public AActor
{
	GENERATED_BODY()

public:
	// 일반 동물의 큐브 기반 접근과 돌진 동작을 준비한다.
	ARegularAnimal();

	// 현재 상태에 맞춰 플레이어 추적, 돌진 예고, 돌진을 갱신한다.
	virtual void Tick(float DeltaTime) override;

	// 칼 공격에 맞았을 때 일반 동물 전투 컴포넌트로 피격 위치를 전달한다.
	void ApplyKnifeHit(const FVector& HitSourceLocation);

	// 칼 피격 직후 잠깐 행동을 멈추는 상태로 전환한다.
	void StunForKnifeHit();

protected:
	// 플레이어를 찾고 돌진 충돌 이벤트를 연결한다.
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal|Prototype")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal|Prototype")
	TObjectPtr<UStaticMeshComponent> PrototypeBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal|Prototype")
	TObjectPtr<UStaticMeshComponent> DashDirectionVisualMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal|Combat")
	TObjectPtr<URegularAnimalCombatComponent> CombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float ApproachSpeed = 220.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float DashSpeed = 850.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float DashStartDistance = 360.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float DashPrepareTime = 0.55f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float DashDuration = 0.45f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float RecoverTime = 0.55f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Combat")
	float HitStunTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float SeparationRadius = 95.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float SeparationPushSpeed = 380.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Combat")
	float DashDamage = 10.0f;

private:
	TWeakObjectPtr<APawn> TargetPlayer;

	ERegularAnimalState CurrentState = ERegularAnimalState::Approaching;

	FVector DashDirection = FVector::ForwardVector;

	float StateElapsedTime = 0.0f;

	bool bDamagedPlayerThisDash = false;

	// 현재 월드의 플레이어 Pawn을 찾아 추적 대상으로 저장한다.
	void CacheTargetPlayer();

	// 플레이어를 향해 천천히 접근한다.
	void UpdateApproach(float DeltaTime);

	// 돌진 방향을 보여주며 잠깐 멈춘다.
	void UpdateDashPreparation(float DeltaTime);

	// 고정된 방향으로 빠르게 돌진한다.
	void UpdateDash(float DeltaTime);

	// 다음 접근을 시작하기 전 짧게 회복한다.
	void UpdateRecover(float DeltaTime);

	// 칼 피격 직후 접근과 돌진을 멈춘 채 기다린다.
	void UpdateHitStun(float DeltaTime);

	// 새 상태로 전환하고 상태 시간을 초기화한다.
	void ChangeState(ERegularAnimalState NewState);

	// 플레이어를 향한 수평 방향을 계산한다.
	FVector GetDirectionToTarget() const;

	// 주어진 방향을 바라보게 회전한다.
	void FaceDirection(const FVector& Direction);

	// 이동을 처리하고 막힌 대상을 확인할 수 있도록 충돌 결과를 돌려준다.
	FHitResult MoveInDirection(const FVector& Direction, float Speed, float DeltaTime);

	// 주변 일반 동물과 겹쳐 보이지 않도록 짧게 밀어낸다.
	void ResolveAnimalSeparation(float DeltaTime);

	// 완전히 같은 위치에 겹쳤을 때 쓸 임시 분리 방향을 계산한다.
	FVector GetFallbackSeparationDirection() const;

	// 목표 플레이어가 게임오버 상태인지 확인한다.
	bool IsTargetPlayerGameOver() const;

	// 돌진 이동 중 막힌 대상이 플레이어면 체력 피해를 준다.
	void HandleDashBlockedHit(const FHitResult& HitResult);
};
