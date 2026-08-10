// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungryHeroMobileInputOrientationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUNGRYHERO_API UHungryHeroMobileInputOrientationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 모바일 가상 조이스틱 입력 방향을 현재 화면 방향에 맞게 보정하는 기본값을 만든다.
	UHungryHeroMobileInputOrientationComponent();

	// 입력 방향을 Android landscape 화면에서 보이는 방향과 월드 이동 방향이 맞도록 변환한다.
	FVector2D TransformInputDirection(const FVector2D& InputDirection) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Mobile")
	float AndroidLandscapeInputYawOffsetDegrees = 0.0f;

private:
	// 현재 빌드에서 모바일 landscape 입력 보정이 필요한지 확인한다.
	bool ShouldApplyAndroidLandscapeOffset() const;
};
