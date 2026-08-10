// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungryHeroMouseFacingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUNGRYHERO_API UHungryHeroMouseFacingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 마우스 이동 방향을 플레이어 정면으로 쓰기 위한 기본값을 만든다.
	UHungryHeroMouseFacingComponent();

	// 마우스 위아래 이동 입력을 바라볼 방향 값으로 저장한다.
	void SetMouseFacingForward(float Value);

	// 마우스 좌우 이동 입력을 바라볼 방향 값으로 저장한다.
	void SetMouseFacingRight(float Value);

	// 이미 계산된 입력 방향을 한 번에 저장한다.
	void SetMouseFacingDirection(const FVector2D& InputDirection);

	// 마우스 이동 입력을 읽고 소유 액터의 정면 방향을 갱신한다.
	void UpdateFacing(float DeltaTime, bool bShouldStopFacing);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	float MouseFacingTurnSpeed = 18.0f;

private:
	float MouseFacingForwardValue = 0.0f;

	float MouseFacingRightValue = 0.0f;

	bool bHasMouseFacingInputThisFrame = false;

	bool bConfiguredGameInputMode = false;

	// 소유 컨트롤러가 준비된 뒤 마우스 이동 입력이 게임에 들어오도록 보장한다.
	void EnsureGameInputMode();

	// 축 바인딩이 마우스 이동 값을 받지 못한 프레임에는 컨트롤러에서 마우스 이동 값을 직접 읽는다.
	void ReadMouseFacingInputFromController();

	// 현재 프레임에 모은 마우스 입력으로 소유 액터를 회전한다.
	void ApplyFacingInput(float DeltaTime);

	// 입력 방향을 기준으로 소유 액터가 점진적으로 회전하게 한다.
	void RotateOwnerTowardInputDirection(const FVector& InputDirection, float DeltaTime) const;

	// 현재 프레임 입력 값을 비운다.
	void ClearFrameInput();
};
