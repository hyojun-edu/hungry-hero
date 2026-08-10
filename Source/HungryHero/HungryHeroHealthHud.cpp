// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryHeroHealthHud.h"

#include "Engine/Canvas.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "HungryHeroHealthComponent.h"
#include "HungryHeroKnifeAttackComponent.h"
#include "HungryHeroScoreComponent.h"

void AHungryHeroHealthHud::DrawHUD()
{
	Super::DrawHUD();

	UHungryHeroHealthComponent* HealthComponent = FindPlayerHealthComponent();
	if (!HealthComponent)
	{
		return;
	}

	DrawHealthBar(HealthComponent);

	if (UHungryHeroScoreComponent* ScoreComponent = FindPlayerScoreComponent())
	{
		DrawScoreText(ScoreComponent);
	}

	if (UHungryHeroKnifeAttackComponent* KnifeAttackComponent = FindPlayerKnifeAttackComponent())
	{
		DrawAttackCooldown(KnifeAttackComponent);
	}

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

UHungryHeroScoreComponent* AHungryHeroHealthHud::FindPlayerScoreComponent() const
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

	return ControlledPawn->FindComponentByClass<UHungryHeroScoreComponent>();
}

UHungryHeroKnifeAttackComponent* AHungryHeroHealthHud::FindPlayerKnifeAttackComponent() const
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

	return ControlledPawn->FindComponentByClass<UHungryHeroKnifeAttackComponent>();
}

float AHungryHeroHealthHud::GetHudScale() const
{
	if (!Canvas)
	{
		return 1.0f;
	}

	const float ShortSide = FMath::Min(static_cast<float>(Canvas->SizeX), static_cast<float>(Canvas->SizeY));
	return FMath::Clamp(ShortSide / 720.0f, 0.9f, 1.4f);
}

void AHungryHeroHealthHud::DrawHealthBar(const UHungryHeroHealthComponent* HealthComponent)
{
	if (!Canvas || !HealthComponent)
	{
		return;
	}

	const float HudScale = GetHudScale();
	const float BarX = 48.0f * HudScale;
	const float BarY = 48.0f * HudScale;
	const float BarWidth = 320.0f * HudScale;
	const float BarHeight = 28.0f * HudScale;
	const float HealthWidth = BarWidth * HealthComponent->GetHealthPercent();

	DrawRect(FLinearColor(0.05f, 0.05f, 0.05f, 0.85f), BarX, BarY, BarWidth, BarHeight);
	DrawRect(FLinearColor(0.85f, 0.08f, 0.05f, 0.95f), BarX, BarY, HealthWidth, BarHeight);

	const FString HealthText = FString::Printf(
		TEXT("Health %.0f / %.0f"),
		HealthComponent->GetCurrentHealth(),
		HealthComponent->GetMaxHealth());
	DrawText(HealthText, FLinearColor::White, BarX, BarY + BarHeight + (8.0f * HudScale), nullptr, HudScale, false);
}

void AHungryHeroHealthHud::DrawScoreText(const UHungryHeroScoreComponent* ScoreComponent)
{
	if (!Canvas || !ScoreComponent)
	{
		return;
	}

	const float HudScale = GetHudScale();
	const FString ScoreText = FString::Printf(TEXT("Score %d"), ScoreComponent->GetCurrentScore());
	DrawText(ScoreText, FLinearColor::Yellow, 48.0f * HudScale, 116.0f * HudScale, nullptr, 1.2f * HudScale, false);
}

void AHungryHeroHealthHud::DrawAttackCooldown(const UHungryHeroKnifeAttackComponent* KnifeAttackComponent)
{
	if (!Canvas || !KnifeAttackComponent)
	{
		return;
	}

	const float HudScale = GetHudScale();
	const float BarX = 48.0f * HudScale;
	const float BarY = 156.0f * HudScale;
	const float BarWidth = 220.0f * HudScale;
	const float BarHeight = 18.0f * HudScale;
	const float ReadyWidth = BarWidth * KnifeAttackComponent->GetAttackCooldownPercent();
	const float CooldownRemaining = KnifeAttackComponent->GetAttackCooldownRemaining();

	DrawRect(FLinearColor(0.05f, 0.05f, 0.05f, 0.85f), BarX, BarY, BarWidth, BarHeight);
	DrawRect(FLinearColor(0.1f, 0.55f, 1.0f, 0.95f), BarX, BarY, ReadyWidth, BarHeight);

	const FString CooldownText = CooldownRemaining > 0.0f
		? FString::Printf(TEXT("Attack %.1fs"), CooldownRemaining)
		: TEXT("Attack Ready");
	DrawText(CooldownText, FLinearColor::White, BarX, BarY + BarHeight + (6.0f * HudScale), nullptr, HudScale, false);
}

void AHungryHeroHealthHud::DrawGameOverText()
{
	if (!Canvas)
	{
		return;
	}

	const float HudScale = GetHudScale();
	const FString GameOverText = TEXT("GAME OVER");
	const float TextX = (Canvas->SizeX * 0.5f) - (140.0f * HudScale);
	const float TextY = Canvas->SizeY * 0.45f;

	DrawText(GameOverText, FLinearColor::Red, TextX, TextY, nullptr, 2.5f * HudScale, false);
}
