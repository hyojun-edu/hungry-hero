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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food|Prototype")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food|Prototype")
	TObjectPtr<UStaticMeshComponent> PrototypeFoodMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food|Prototype")
	TObjectPtr<UTextRenderComponent> FoodLabelText;
};
