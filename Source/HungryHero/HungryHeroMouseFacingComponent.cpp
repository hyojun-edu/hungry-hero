// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroMouseFacingComponent.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"

UHungryHeroMouseFacingComponent::UHungryHeroMouseFacingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHungryHeroMouseFacingComponent::SetMouseFacingForward(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	MouseFacingForwardValue = Value;
	bHasMouseFacingInputThisFrame = true;
}

void UHungryHeroMouseFacingComponent::SetMouseFacingRight(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	MouseFacingRightValue = Value;
	bHasMouseFacingInputThisFrame = true;
}

void UHungryHeroMouseFacingComponent::SetMouseFacingDirection(const FVector2D& InputDirection)
{
	if (InputDirection.IsNearlyZero())
	{
		return;
	}

	MouseFacingForwardValue = InputDirection.X;
	MouseFacingRightValue = InputDirection.Y;
	bHasMouseFacingInputThisFrame = true;
}

void UHungryHeroMouseFacingComponent::UpdateFacing(float DeltaTime, bool bShouldStopFacing)
{
	EnsureGameInputMode();

	if (bShouldStopFacing)
	{
		ClearFrameInput();
		return;
	}

	ReadMouseFacingInputFromController();
	ApplyFacingInput(DeltaTime);
	ClearFrameInput();
}

void UHungryHeroMouseFacingComponent::EnsureGameInputMode()
{
	if (bConfiguredGameInputMode)
	{
		return;
	}

	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	APlayerController* PlayerController = OwnerPawn ? Cast<APlayerController>(OwnerPawn->GetController()) : nullptr;
	if (!PlayerController)
	{
		return;
	}

	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(FInputModeGameOnly());
	bConfiguredGameInputMode = true;
}

void UHungryHeroMouseFacingComponent::ReadMouseFacingInputFromController()
{
	if (bHasMouseFacingInputThisFrame)
	{
		return;
	}

	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	APlayerController* PlayerController = OwnerPawn ? Cast<APlayerController>(OwnerPawn->GetController()) : nullptr;
	if (!PlayerController)
	{
		return;
	}

	float MouseDeltaX = PlayerController->GetInputAnalogKeyState(EKeys::MouseX);
	float MouseDeltaY = PlayerController->GetInputAnalogKeyState(EKeys::MouseY);
	if (FMath::IsNearlyZero(MouseDeltaX) && FMath::IsNearlyZero(MouseDeltaY))
	{
		PlayerController->GetInputMouseDelta(MouseDeltaX, MouseDeltaY);
	}

	if (FMath::IsNearlyZero(MouseDeltaX) && FMath::IsNearlyZero(MouseDeltaY))
	{
		return;
	}

	MouseFacingForwardValue = MouseDeltaY;
	MouseFacingRightValue = MouseDeltaX;
	bHasMouseFacingInputThisFrame = true;
}

void UHungryHeroMouseFacingComponent::ApplyFacingInput(float DeltaTime)
{
	if (!bHasMouseFacingInputThisFrame)
	{
		return;
	}

	RotateOwnerTowardInputDirection(
		FVector(MouseFacingForwardValue, MouseFacingRightValue, 0.0f),
		DeltaTime);
}

void UHungryHeroMouseFacingComponent::RotateOwnerTowardInputDirection(const FVector& InputDirection, float DeltaTime) const
{
	AActor* Owner = GetOwner();
	if (!Owner || InputDirection.IsNearlyZero())
	{
		return;
	}

	const FRotator TargetRotation = InputDirection.Rotation();
	const FRotator NewRotation = FMath::RInterpTo(
		Owner->GetActorRotation(),
		FRotator(0.0f, TargetRotation.Yaw, 0.0f),
		DeltaTime,
		MouseFacingTurnSpeed);
	Owner->SetActorRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
}

void UHungryHeroMouseFacingComponent::ClearFrameInput()
{
	bHasMouseFacingInputThisFrame = false;
	MouseFacingForwardValue = 0.0f;
	MouseFacingRightValue = 0.0f;
}
