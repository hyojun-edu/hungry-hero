// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroKnifeAttackComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

UHungryHeroKnifeAttackComponent::UHungryHeroKnifeAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHungryHeroKnifeAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateAttackVisualMesh();
}

void UHungryHeroKnifeAttackComponent::StartAttack()
{
	if (!AttackVisualMesh)
	{
		return;
	}

	AttackVisualMesh->SetHiddenInGame(false);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(AttackVisibleTimerHandle);
		World->GetTimerManager().SetTimer(
			AttackVisibleTimerHandle,
			this,
			&UHungryHeroKnifeAttackComponent::HideAttackVisual,
			AttackVisibleTime,
			false);
	}
}

void UHungryHeroKnifeAttackComponent::CreateAttackVisualMesh()
{
	AActor* Owner = GetOwner();
	if (!Owner || AttackVisualMesh)
	{
		return;
	}

	AttackVisualMesh = NewObject<UStaticMeshComponent>(Owner, TEXT("KnifeAttackVisualMesh"));
	if (!AttackVisualMesh)
	{
		return;
	}

	if (UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube")))
	{
		AttackVisualMesh->SetStaticMesh(CubeMesh);
	}

	Owner->AddInstanceComponent(AttackVisualMesh);
	AttackVisualMesh->SetupAttachment(Owner->GetRootComponent());
	AttackVisualMesh->SetRelativeLocation(FVector(90.0f, 0.0f, 0.0f));
	AttackVisualMesh->SetRelativeScale3D(FVector(1.1f, 0.16f, 0.08f));
	AttackVisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackVisualMesh->SetHiddenInGame(true);
	AttackVisualMesh->RegisterComponent();
}

void UHungryHeroKnifeAttackComponent::HideAttackVisual()
{
	if (AttackVisualMesh)
	{
		AttackVisualMesh->SetHiddenInGame(true);
	}
}
