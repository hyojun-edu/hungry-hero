// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroPlayerCharacter.h"

#include "HungryHeroHealthComponent.h"
#include "HungryHeroKnifeAttackComponent.h"
#include "HungryHeroMouseFacingComponent.h"
#include "HungryHeroScoreComponent.h"
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
	HealthComponent = CreateDefaultSubobject<UHungryHeroHealthComponent>(TEXT("HealthComponent"));
	ScoreComponent = CreateDefaultSubobject<UHungryHeroScoreComponent>(TEXT("ScoreComponent"));
	MouseFacingComponent = CreateDefaultSubobject<UHungryHeroMouseFacingComponent>(TEXT("MouseFacingComponent"));
}

void AHungryHeroPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsGameOver())
	{
		GetCharacterMovement()->StopMovementImmediately();
		if (MouseFacingComponent)
		{
			MouseFacingComponent->UpdateFacing(DeltaTime, true);
		}
		return;
	}

	if (MouseFacingComponent)
	{
		MouseFacingComponent->UpdateFacing(DeltaTime, false);
	}

	if (KnifeAttackComponent)
	{
		KnifeAttackComponent->UpdateAutoAttack(DeltaTime);
	}
}

void AHungryHeroPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AHungryHeroPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AHungryHeroPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MouseFaceForward"), this, &AHungryHeroPlayerCharacter::SetMouseFacingForward);
	PlayerInputComponent->BindAxis(TEXT("MouseFaceRight"), this, &AHungryHeroPlayerCharacter::SetMouseFacingRight);
}

void AHungryHeroPlayerCharacter::MoveForward(float Value)
{
	if (IsGameOver())
	{
		return;
	}

	AddMovementInput(FVector::ForwardVector, Value);
}

void AHungryHeroPlayerCharacter::MoveRight(float Value)
{
	if (IsGameOver())
	{
		return;
	}

	AddMovementInput(FVector::RightVector, Value);
}

void AHungryHeroPlayerCharacter::SetMouseFacingForward(float Value)
{
	if (IsGameOver())
	{
		return;
	}

	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	if (MouseFacingComponent)
	{
		MouseFacingComponent->SetMouseFacingForward(Value);
	}
}

void AHungryHeroPlayerCharacter::SetMouseFacingRight(float Value)
{
	if (IsGameOver())
	{
		return;
	}

	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	if (MouseFacingComponent)
	{
		MouseFacingComponent->SetMouseFacingRight(Value);
	}
}

bool AHungryHeroPlayerCharacter::IsGameOver() const
{
	return HealthComponent && HealthComponent->IsGameOver();
}
