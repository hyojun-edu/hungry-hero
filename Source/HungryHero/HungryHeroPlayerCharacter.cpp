// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroPlayerCharacter.h"

#include "HungryHeroKnifeAttackComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

AHungryHeroPlayerCharacter::AHungryHeroPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.0f, 88.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxAcceleration = 4000.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 4000.0f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	PrototypeBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrototypeBodyMesh"));
	PrototypeBodyMesh->SetupAttachment(GetCapsuleComponent());
	PrototypeBodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PrototypeBodyMesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		PrototypeBodyMesh->SetStaticMesh(CubeMesh.Object);
	}

	KnifeAttackComponent = CreateDefaultSubobject<UHungryHeroKnifeAttackComponent>(TEXT("KnifeAttackComponent"));
}

void AHungryHeroPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateFacingFromMouseInput(DeltaTime);
	bHasMouseFacingInputThisFrame = false;
	MouseFacingForwardValue = 0.0f;
	MouseFacingRightValue = 0.0f;
}

void AHungryHeroPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AHungryHeroPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AHungryHeroPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MouseFaceForward"), this, &AHungryHeroPlayerCharacter::SetMouseFacingForward);
	PlayerInputComponent->BindAxis(TEXT("MouseFaceRight"), this, &AHungryHeroPlayerCharacter::SetMouseFacingRight);
	PlayerInputComponent->BindAction(TEXT("KnifeAttack"), IE_Pressed, this, &AHungryHeroPlayerCharacter::Attack);
}

void AHungryHeroPlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);
}

void AHungryHeroPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector, Value);
}

void AHungryHeroPlayerCharacter::SetMouseFacingForward(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	MouseFacingForwardValue = Value;
	bHasMouseFacingInputThisFrame = true;
}

void AHungryHeroPlayerCharacter::SetMouseFacingRight(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	MouseFacingRightValue = Value;
	bHasMouseFacingInputThisFrame = true;
}

void AHungryHeroPlayerCharacter::UpdateFacingFromMouseInput(float DeltaTime)
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

void AHungryHeroPlayerCharacter::RotateTowardInputDirection(const FVector& InputDirection, float DeltaTime, float TurnSpeed)
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

void AHungryHeroPlayerCharacter::Attack()
{
	if (KnifeAttackComponent)
	{
		KnifeAttackComponent->StartAttack();
	}
}
