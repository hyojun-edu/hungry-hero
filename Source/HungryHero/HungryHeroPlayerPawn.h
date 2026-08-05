// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HungryHeroPlayerPawn.generated.h"

class UFloatingPawnMovement;
class UStaticMeshComponent;

UCLASS()
class HUNGRYHERO_API AHungryHeroPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// 큐브 기반 플레이어 Pawn의 기본 컴포넌트와 이동 설정을 만든다.
	AHungryHeroPlayerPawn();

protected:
	// 플레이어 이동 입력 축을 Pawn 이동 함수에 연결한다.
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	// 앞뒤 이동 입력을 이동 컴포넌트에 전달한다.
	void MoveForward(float Value);

	// 좌우 이동 입력을 이동 컴포넌트에 전달한다.
	void MoveRight(float Value);
};
