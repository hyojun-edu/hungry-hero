// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroMobileInputOrientationComponent.h"

UHungryHeroMobileInputOrientationComponent::UHungryHeroMobileInputOrientationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FVector2D UHungryHeroMobileInputOrientationComponent::TransformInputDirection(const FVector2D& InputDirection) const
{
	if (!ShouldApplyAndroidLandscapeOffset() || InputDirection.IsNearlyZero())
	{
		return InputDirection;
	}

	const float RotationRadians = FMath::DegreesToRadians(AndroidLandscapeInputYawOffsetDegrees);
	const float CosAngle = FMath::Cos(RotationRadians);
	const float SinAngle = FMath::Sin(RotationRadians);

	return FVector2D(
		InputDirection.X * CosAngle - InputDirection.Y * SinAngle,
		InputDirection.X * SinAngle + InputDirection.Y * CosAngle);
}

bool UHungryHeroMobileInputOrientationComponent::ShouldApplyAndroidLandscapeOffset() const
{
#if PLATFORM_ANDROID
	return true;
#else
	return false;
#endif
}
