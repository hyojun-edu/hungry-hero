// Copyright Epic Games, Inc. All Rights Reserved.

#include "RegularAnimal.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "HungryHeroHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RegularAnimalCombatComponent.h"
#include "UObject/ConstructorHelpers.h"

ARegularAnimal::ARegularAnimal()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->InitSphereRadius(44.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECC_Pawn);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);

	PrototypeBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrototypeBodyMesh"));
	PrototypeBodyMesh->SetupAttachment(CollisionComponent);
	PrototypeBodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PrototypeBodyMesh->SetRelativeScale3D(FVector(0.8f, 0.55f, 0.45f));

	DashDirectionVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DashDirectionVisualMesh"));
	DashDirectionVisualMesh->SetupAttachment(CollisionComponent);
	DashDirectionVisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DashDirectionVisualMesh->SetRelativeLocation(FVector(95.0f, 0.0f, -20.0f));
	DashDirectionVisualMesh->SetRelativeScale3D(FVector(1.25f, 0.08f, 0.04f));
	DashDirectionVisualMesh->SetHiddenInGame(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		PrototypeBodyMesh->SetStaticMesh(CubeMesh.Object);
		DashDirectionVisualMesh->SetStaticMesh(CubeMesh.Object);
	}

	CombatComponent = CreateDefaultSubobject<URegularAnimalCombatComponent>(TEXT("CombatComponent"));
}

void ARegularAnimal::BeginPlay()
{
	Super::BeginPlay();

	CacheTargetPlayer();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARegularAnimal::HandleOverlap);
}

void ARegularAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetPlayer.IsValid())
	{
		CacheTargetPlayer();
	}

	StateElapsedTime += DeltaTime;

	switch (CurrentState)
	{
	case ERegularAnimalState::Approaching:
		UpdateApproach(DeltaTime);
		break;
	case ERegularAnimalState::PreparingDash:
		UpdateDashPreparation(DeltaTime);
		break;
	case ERegularAnimalState::Dashing:
		UpdateDash(DeltaTime);
		break;
	case ERegularAnimalState::Recovering:
		UpdateRecover(DeltaTime);
		break;
	default:
		break;
	}

	ResolveAnimalSeparation(DeltaTime);
}

void ARegularAnimal::ApplyKnifeHit()
{
	if (CombatComponent)
	{
		CombatComponent->ApplyKnifeHit();
	}
}

void ARegularAnimal::CacheTargetPlayer()
{
	TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
}

void ARegularAnimal::UpdateApproach(float DeltaTime)
{
	const FVector DirectionToTarget = GetDirectionToTarget();
	if (DirectionToTarget.IsNearlyZero())
	{
		return;
	}

	FaceDirection(DirectionToTarget);
	MoveInDirection(DirectionToTarget, ApproachSpeed, DeltaTime);

	const APawn* PlayerPawn = TargetPlayer.Get();
	if (PlayerPawn && FVector::Dist2D(GetActorLocation(), PlayerPawn->GetActorLocation()) <= DashStartDistance)
	{
		DashDirection = DirectionToTarget;
		ChangeState(ERegularAnimalState::PreparingDash);
	}
}

void ARegularAnimal::UpdateDashPreparation(float DeltaTime)
{
	FaceDirection(DashDirection);

	if (StateElapsedTime >= DashPrepareTime)
	{
		ChangeState(ERegularAnimalState::Dashing);
	}
}

void ARegularAnimal::UpdateDash(float DeltaTime)
{
	MoveInDirection(DashDirection, DashSpeed, DeltaTime);

	if (StateElapsedTime >= DashDuration)
	{
		ChangeState(ERegularAnimalState::Recovering);
	}
}

void ARegularAnimal::UpdateRecover(float DeltaTime)
{
	if (StateElapsedTime >= RecoverTime)
	{
		ChangeState(ERegularAnimalState::Approaching);
	}
}

void ARegularAnimal::ChangeState(ERegularAnimalState NewState)
{
	CurrentState = NewState;
	StateElapsedTime = 0.0f;

	const bool bShowsDashDirection = CurrentState == ERegularAnimalState::PreparingDash || CurrentState == ERegularAnimalState::Dashing;
	DashDirectionVisualMesh->SetHiddenInGame(!bShowsDashDirection);

	if (CurrentState == ERegularAnimalState::Dashing)
	{
		bDamagedPlayerThisDash = false;
	}
}

FVector ARegularAnimal::GetDirectionToTarget() const
{
	const APawn* PlayerPawn = TargetPlayer.Get();
	if (!PlayerPawn)
	{
		return FVector::ZeroVector;
	}

	FVector Direction = PlayerPawn->GetActorLocation() - GetActorLocation();
	Direction.Z = 0.0f;
	return Direction.GetSafeNormal();
}

void ARegularAnimal::FaceDirection(const FVector& Direction)
{
	if (Direction.IsNearlyZero())
	{
		return;
	}

	SetActorRotation(FRotator(0.0f, Direction.Rotation().Yaw, 0.0f));
}

void ARegularAnimal::MoveInDirection(const FVector& Direction, float Speed, float DeltaTime)
{
	if (Direction.IsNearlyZero())
	{
		return;
	}

	FHitResult HitResult;
	AddActorWorldOffset(Direction * Speed * DeltaTime, true, &HitResult);
}

void ARegularAnimal::ResolveAnimalSeparation(float DeltaTime)
{
	UWorld* World = GetWorld();
	if (!World || SeparationRadius <= 0.0f || SeparationPushSpeed <= 0.0f)
	{
		return;
	}

	const float SeparationRadiusSquared = FMath::Square(SeparationRadius);

	for (TActorIterator<ARegularAnimal> AnimalIterator(World); AnimalIterator; ++AnimalIterator)
	{
		ARegularAnimal* OtherAnimal = *AnimalIterator;
		if (!IsValid(OtherAnimal) || OtherAnimal == this)
		{
			continue;
		}

		FVector OffsetFromOther = GetActorLocation() - OtherAnimal->GetActorLocation();
		OffsetFromOther.Z = 0.0f;

		const float DistanceSquared = OffsetFromOther.SizeSquared();
		if (DistanceSquared >= SeparationRadiusSquared)
		{
			continue;
		}

		FVector PushDirection = OffsetFromOther.GetSafeNormal();
		if (PushDirection.IsNearlyZero())
		{
			PushDirection = GetFallbackSeparationDirection();
		}

		const float Distance = FMath::Sqrt(DistanceSquared);
		const float NeededPushDistance = SeparationRadius - Distance;
		const float PushDistance = FMath::Min(NeededPushDistance, SeparationPushSpeed * DeltaTime);

		FHitResult HitResult;
		AddActorWorldOffset(PushDirection * PushDistance, true, &HitResult);
	}
}

FVector ARegularAnimal::GetFallbackSeparationDirection() const
{
	const float AngleRadians = static_cast<float>(GetUniqueID() % 360) * UE_PI / 180.0f;
	return FVector(FMath::Cos(AngleRadians), FMath::Sin(AngleRadians), 0.0f);
}

void ARegularAnimal::HandleOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (CurrentState != ERegularAnimalState::Dashing || bDamagedPlayerThisDash || !OtherActor)
	{
		return;
	}

	if (UHungryHeroHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHungryHeroHealthComponent>())
	{
		HealthComponent->ApplyDamage(DashDamage);
		bDamagedPlayerThisDash = true;
	}
}
