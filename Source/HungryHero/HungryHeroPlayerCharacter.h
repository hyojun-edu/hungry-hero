// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HungryHeroPlayerCharacter.generated.h"

class UHungryHeroKnifeAttackComponent;
class UHungryHeroHealthComponent;
class UHungryHeroMouseFacingComponent;
class UHungryHeroScoreComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class HUNGRYHERO_API AHungryHeroPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Blueprint에서 외형을 조정할 수 있는 플레이어 Character 기본 구조를 만든다.
	AHungryHeroPlayerCharacter();

	// 마우스 이동 입력에 따라 바라보는 방향을 갱신한다.
	virtual void Tick(float DeltaTime) override;

protected:
	// 플레이어 이동 입력 축을 Character 이동 함수에 연결한다.
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Prototype")
	TObjectPtr<UStaticMeshComponent> PrototypeBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Attack")
	TObjectPtr<UHungryHeroKnifeAttackComponent> KnifeAttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Health")
	TObjectPtr<UHungryHeroHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Score")
	TObjectPtr<UHungryHeroScoreComponent> ScoreComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Input")
	TObjectPtr<UHungryHeroMouseFacingComponent> MouseFacingComponent;

private:
	// 앞뒤 이동 입력을 이동 컴포넌트에 전달한다.
	void MoveForward(float Value);

	// 좌우 이동 입력을 이동 컴포넌트에 전달한다.
	void MoveRight(float Value);

	// 마우스 위아래 이동 입력을 바라볼 방향 값으로 저장한다.
	void SetMouseFacingForward(float Value);

	// 마우스 좌우 이동 입력을 바라볼 방향 값으로 저장한다.
	void SetMouseFacingRight(float Value);

	// 체력이 0이 되어 플레이 조작을 막아야 하는지 확인한다.
	bool IsGameOver() const;
};
