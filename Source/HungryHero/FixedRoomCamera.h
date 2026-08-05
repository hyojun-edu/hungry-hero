// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FixedRoomCamera.generated.h"

class UCameraComponent;

UCLASS()
class HUNGRYHERO_API AFixedRoomCamera : public AActor
{
	GENERATED_BODY()

public:
	// 방 전체를 내려다보는 고정 카메라 컴포넌트를 만든다.
	AFixedRoomCamera();

	// 에디터 배치 중에도 카메라가 목표 위치를 바라보도록 회전을 갱신한다.
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// 플레이 시작 시 첫 번째 플레이어의 시점을 이 카메라로 고정한다.
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector TargetLocation;
};
