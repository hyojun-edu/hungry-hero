// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HungryHeroPlayerPawn.generated.h"

class UFloatingPawnMovement;
class UHungryHeroKnifeAttackComponent;
class UStaticMeshComponent;

UCLASS()
class HUNGRYHERO_API AHungryHeroPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// 큐브 기반 플레이어 Pawn의 기본 컴포넌트와 이동 설정을 만든다.
	AHungryHeroPlayerPawn();

	// 마우스 이동 입력에 따라 바라보는 방향을 갱신한다.
	virtual void Tick(float DeltaTime) override;

protected:
	// 플레이어 이동 입력 축을 Pawn 이동 함수에 연결한다.
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<UHungryHeroKnifeAttackComponent> KnifeAttackComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float MouseFacingTurnSpeed = 18.0f;

	float MouseFacingForwardValue = 0.0f;

	float MouseFacingRightValue = 0.0f;

	bool bHasMouseFacingInputThisFrame = false;

	// 앞뒤 이동 입력을 이동 컴포넌트에 전달한다.
	void MoveForward(float Value);

	// 좌우 이동 입력을 이동 컴포넌트에 전달한다.
	void MoveRight(float Value);

	// 마우스 위아래 이동 입력을 바라볼 방향 값으로 저장한다.
	void SetMouseFacingForward(float Value);

	// 마우스 좌우 이동 입력을 바라볼 방향 값으로 저장한다.
	void SetMouseFacingRight(float Value);

	// 마우스 이동 방향을 플레이어 정면으로 사용한다.
	void UpdateFacingFromMouseInput(float DeltaTime);

	// 입력 방향을 기준으로 플레이어가 점진적으로 회전하게 한다.
	void RotateTowardInputDirection(const FVector& InputDirection, float DeltaTime, float TurnSpeed);

	// 단발 칼 공격 입력을 공격 컴포넌트에 전달한다.
	void Attack();
};
