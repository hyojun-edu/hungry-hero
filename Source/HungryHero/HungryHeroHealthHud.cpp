// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroHealthHud.h"

#include "Engine/Canvas.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "HungryHeroHealthComponent.h"

void AHungryHeroHealthHud::DrawHUD()
{
	Super::DrawHUD();

	UHungryHeroHealthComponent* HealthComponent = FindPlayerHealthComponent();
	if (!HealthComponent)
	{
		return;
	}

	DrawHealthBar(HealthComponent);

	if (HealthComponent->IsGameOver())
	{
		DrawGameOverText();
	}
}

UHungryHeroHealthComponent* AHungryHeroHealthHud::FindPlayerHealthComponent() const
{
	if (!PlayerOwner)
	{
		return nullptr;
	}

	APawn* ControlledPawn = PlayerOwner->GetPawn();
	if (!ControlledPawn)
	{
		return nullptr;
	}

	return ControlledPawn->FindComponentByClass<UHungryHeroHealthComponent>();
}

void AHungryHeroHealthHud::DrawHealthBar(const UHungryHeroHealthComponent* HealthComponent)
{
	if (!Canvas || !HealthComponent)
	{
		return;
	}

	const float BarX = 48.0f;
	const float BarY = 48.0f;
	const float BarWidth = 320.0f;
	const float BarHeight = 28.0f;
	const float HealthWidth = BarWidth * HealthComponent->GetHealthPercent();

	DrawRect(FLinearColor(0.05f, 0.05f, 0.05f, 0.85f), BarX, BarY, BarWidth, BarHeight);
	DrawRect(FLinearColor(0.85f, 0.08f, 0.05f, 0.95f), BarX, BarY, HealthWidth, BarHeight);

	const FString HealthText = FString::Printf(
		TEXT("Health %.0f / %.0f"),
		HealthComponent->GetCurrentHealth(),
		HealthComponent->GetMaxHealth());
	DrawText(HealthText, FLinearColor::White, BarX, BarY + BarHeight + 8.0f, nullptr, 1.0f, false);
}

void AHungryHeroHealthHud::DrawGameOverText()
{
	if (!Canvas)
	{
		return;
	}

	const FString GameOverText = TEXT("GAME OVER");
	const float TextX = (Canvas->SizeX * 0.5f) - 140.0f;
	const float TextY = Canvas->SizeY * 0.45f;

	DrawText(GameOverText, FLinearColor::Red, TextX, TextY, nullptr, 2.5f, false);
}
