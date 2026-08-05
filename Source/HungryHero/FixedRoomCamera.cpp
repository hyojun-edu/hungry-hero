// Copyright Epic Games, Inc. All Rights Reserved.

#include "FixedRoomCamera.h"

#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AFixedRoomCamera::AFixedRoomCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SetRootComponent(CameraComponent);
	CameraComponent->SetAutoActivate(true);

	const FVector CameraLocation(-900.0f, 0.0f, 900.0f);
	TargetLocation = FVector::ZeroVector;

	SetActorLocation(CameraLocation);
	SetActorRotation((TargetLocation - CameraLocation).Rotation());
	CameraComponent->SetFieldOfView(60.0f);
}

void AFixedRoomCamera::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const FVector DirectionToTarget = TargetLocation - GetActorLocation();
	if (!DirectionToTarget.IsNearlyZero())
	{
		SetActorRotation(DirectionToTarget.Rotation());
	}
}

void AFixedRoomCamera::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		FViewTargetTransitionParams TransitionParams;
		PlayerController->SetViewTarget(this, TransitionParams);
	}
}
