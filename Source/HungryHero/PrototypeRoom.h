// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrototypeRoom.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UDirectionalLightComponent;

UCLASS()
class HUNGRYHERO_API APrototypeRoom : public AActor
{
	GENERATED_BODY()

public:
	// 큐브 메시로 바닥과 네 벽을 가진 프로토타입 방을 구성한다.
	APrototypeRoom();

private:
	UPROPERTY(VisibleAnywhere, Category = "Room")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Room")
	TObjectPtr<UStaticMeshComponent> FloorMesh;

	UPROPERTY(VisibleAnywhere, Category = "Room")
	TObjectPtr<UStaticMeshComponent> NorthWallMesh;

	UPROPERTY(VisibleAnywhere, Category = "Room")
	TObjectPtr<UStaticMeshComponent> SouthWallMesh;

	UPROPERTY(VisibleAnywhere, Category = "Room")
	TObjectPtr<UStaticMeshComponent> EastWallMesh;

	UPROPERTY(VisibleAnywhere, Category = "Room")
	TObjectPtr<UStaticMeshComponent> WestWallMesh;

	UPROPERTY(VisibleAnywhere, Category = "Room")
	TObjectPtr<UDirectionalLightComponent> RoomLight;

	// 방을 구성하는 큐브 메시의 공통 충돌과 메시를 설정한다.
	void ConfigureRoomMesh(UStaticMeshComponent* MeshComponent, UStaticMesh* CubeMesh) const;
};
