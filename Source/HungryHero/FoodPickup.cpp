// Copyright Epic Games, Inc. All Rights Reserved.

#include "FoodPickup.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/StaticMesh.h"
#include "HungryHeroHealthComponent.h"
#include "HungryHeroScoreComponent.h"
#include "UObject/ConstructorHelpers.h"

AFoodPickup::AFoodPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->InitSphereRadius(30.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);

	PrototypeFoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrototypeFoodMesh"));
	PrototypeFoodMesh->SetupAttachment(CollisionComponent);
	PrototypeFoodMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PrototypeFoodMesh->SetRelativeScale3D(FVector(0.45f, 0.45f, 0.25f));

	FoodLabelText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("FoodLabelText"));
	FoodLabelText->SetupAttachment(CollisionComponent);
	FoodLabelText->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FoodLabelText->SetRelativeLocation(FVector(0.0f, 0.0f, 42.0f));
	FoodLabelText->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	FoodLabelText->SetHorizontalAlignment(EHTA_Center);
	FoodLabelText->SetVerticalAlignment(EVRTA_TextCenter);
	FoodLabelText->SetText(FText::FromString(TEXT("FOOD")));
	FoodLabelText->SetTextRenderColor(FColor::Orange);
	FoodLabelText->SetWorldSize(26.0f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		PrototypeFoodMesh->SetStaticMesh(SphereMesh.Object);
	}
}

void AFoodPickup::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFoodPickup::HandleOverlap);
}

void AFoodPickup::HandleOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	UHungryHeroHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHungryHeroHealthComponent>();
	UHungryHeroScoreComponent* ScoreComponent = OtherActor->FindComponentByClass<UHungryHeroScoreComponent>();
	if (!HealthComponent || !ScoreComponent)
	{
		return;
	}

	if (HealthComponent->IsGameOver())
	{
		return;
	}

	HealthComponent->Heal(HealAmount);
	ScoreComponent->AddFoodScore();
	Destroy();
}
