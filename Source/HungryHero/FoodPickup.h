// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS(Blueprintable)
class HUNGRYHERO_API AFoodPickup : public AActor
{
	GENERATED_BODY()

public:
	// 플레이어가 알아보기 쉬운 프로토타입 음식 표시 액터를 만든다.
	AFoodPickup();

protected:
	// 음식 획득 충돌 처리를 준비한다.
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food|Prototype")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food|Prototype")
	TObjectPtr<UStaticMeshComponent> PrototypeFoodMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food|Prototype")
	TObjectPtr<UTextRenderComponent> FoodLabelText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Food|Pickup")
	float HealAmount = 20.0f;

private:
	// 플레이어가 음식에 닿으면 체력 회복과 점수 증가를 처리한다.
	UFUNCTION()
	void HandleOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
