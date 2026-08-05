// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrototypeRoom.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

APrototypeRoom::APrototypeRoom()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneRoot);

	NorthWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NorthWallMesh"));
	NorthWallMesh->SetupAttachment(SceneRoot);

	SouthWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SouthWallMesh"));
	SouthWallMesh->SetupAttachment(SceneRoot);

	EastWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EastWallMesh"));
	EastWallMesh->SetupAttachment(SceneRoot);

	WestWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WestWallMesh"));
	WestWallMesh->SetupAttachment(SceneRoot);

	RoomLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("RoomLight"));
	RoomLight->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	UStaticMesh* RoomMesh = CubeMesh.Succeeded() ? CubeMesh.Object : nullptr;

	ConfigureRoomMesh(FloorMesh, RoomMesh);
	ConfigureRoomMesh(NorthWallMesh, RoomMesh);
	ConfigureRoomMesh(SouthWallMesh, RoomMesh);
	ConfigureRoomMesh(EastWallMesh, RoomMesh);
	ConfigureRoomMesh(WestWallMesh, RoomMesh);

	FloorMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -55.0f));
	FloorMesh->SetRelativeScale3D(FVector(12.0f, 12.0f, 0.1f));

	NorthWallMesh->SetRelativeLocation(FVector(0.0f, 600.0f, 45.0f));
	NorthWallMesh->SetRelativeScale3D(FVector(12.0f, 0.2f, 2.0f));

	SouthWallMesh->SetRelativeLocation(FVector(0.0f, -600.0f, 45.0f));
	SouthWallMesh->SetRelativeScale3D(FVector(12.0f, 0.2f, 2.0f));

	EastWallMesh->SetRelativeLocation(FVector(600.0f, 0.0f, 45.0f));
	EastWallMesh->SetRelativeScale3D(FVector(0.2f, 12.0f, 2.0f));

	WestWallMesh->SetRelativeLocation(FVector(-600.0f, 0.0f, 45.0f));
	WestWallMesh->SetRelativeScale3D(FVector(0.2f, 12.0f, 2.0f));

	RoomLight->SetRelativeRotation(FRotator(-60.0f, -35.0f, 0.0f));
	RoomLight->SetIntensity(6.0f);
	RoomLight->SetCastShadows(false);
}

void APrototypeRoom::ConfigureRoomMesh(UStaticMeshComponent* MeshComponent, UStaticMesh* CubeMesh) const
{
	if (!MeshComponent)
	{
		return;
	}

	if (CubeMesh)
	{
		MeshComponent->SetStaticMesh(CubeMesh);
	}

	MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
}
