// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroPlayerPawn.h"

#include "HungryHeroKnifeAttackComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UObject/ConstructorHelpers.h"

AHungryHeroPlayerPawn::AHungryHeroPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	SetRootComponent(BodyMesh);
	BodyMesh->SetCollisionProfileName(TEXT("Pawn"));
	BodyMesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		BodyMesh->SetStaticMesh(CubeMesh.Object);
	}

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->MaxSpeed = 600.0f;
	MovementComponent->Acceleration = 4000.0f;
	MovementComponent->Deceleration = 4000.0f;

	KnifeAttackComponent = CreateDefaultSubobject<UHungryHeroKnifeAttackComponent>(TEXT("KnifeAttackComponent"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AHungryHeroPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateFacingFromMouseInput(DeltaTime);
	bHasMouseFacingInputThisFrame = false;
	MouseFacingForwardValue = 0.0f;
	MouseFacingRightValue = 0.0f;
}

void AHungryHeroPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AHungryHeroPlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AHungryHeroPlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MouseFaceForward"), this, &AHungryHeroPlayerPawn::SetMouseFacingForward);
	PlayerInputComponent->BindAxis(TEXT("MouseFaceRight"), this, &AHungryHeroPlayerPawn::SetMouseFacingRight);
	PlayerInputComponent->BindAction(TEXT("KnifeAttack"), IE_Pressed, this, &AHungryHeroPlayerPawn::Attack);
}

void AHungryHeroPlayerPawn::MoveForward(float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);
}

void AHungryHeroPlayerPawn::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector, Value);
}

void AHungryHeroPlayerPawn::SetMouseFacingForward(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	MouseFacingForwardValue = Value;
	bHasMouseFacingInputThisFrame = true;
}

void AHungryHeroPlayerPawn::SetMouseFacingRight(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	MouseFacingRightValue = Value;
	bHasMouseFacingInputThisFrame = true;
}

void AHungryHeroPlayerPawn::UpdateFacingFromMouseInput(float DeltaTime)
{
	if (!bHasMouseFacingInputThisFrame)
	{
		return;
	}

	RotateTowardInputDirection(
		FVector(MouseFacingForwardValue, MouseFacingRightValue, 0.0f),
		DeltaTime,
		MouseFacingTurnSpeed);
}

void AHungryHeroPlayerPawn::RotateTowardInputDirection(const FVector& InputDirection, float DeltaTime, float TurnSpeed)
{
	if (InputDirection.IsNearlyZero())
	{
		return;
	}

	const FRotator TargetRotation = InputDirection.Rotation();
	const FRotator NewRotation = FMath::RInterpTo(
		GetActorRotation(),
		FRotator(0.0f, TargetRotation.Yaw, 0.0f),
		DeltaTime,
		TurnSpeed);
	SetActorRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
}

void AHungryHeroPlayerPawn::Attack()
{
	if (KnifeAttackComponent)
	{
		KnifeAttackComponent->StartAttack();
	}
}
