// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUDWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Core/BJGameMode.h"

void UGameHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		BJGameMode = GetWorld()->GetAuthGameMode<ABJGameMode>();
		if (BJGameMode)
		{
			BJGameMode->OnRoundStart.AddUObject(this, &UGameHUDWidget::OnStartRound);
			BJGameMode->OnRoundEnd.AddUObject(this, &UGameHUDWidget::OnEndRound);
		}
	}
	
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UGameHUDWidget::OnStartButtonPressed);
	}
	if (HitButton)
	{
		HitButton->OnClicked.AddDynamic(this, &UGameHUDWidget::OnHitButtonPressed);
	}
	if (StandButton)
	{
		StandButton->OnClicked.AddDynamic(this, &UGameHUDWidget::OnStandButtonPressed);
	}
}

void UGameHUDWidget::OnStartButtonPressed() 
{
	if (!BJGameMode) return;
	BJGameMode->StartRound();
}

void UGameHUDWidget::OnHitButtonPressed() 
{
	if (!BJGameMode) return;
	BJGameMode->PlayerHit();
}

void UGameHUDWidget::OnStandButtonPressed() 
{
	if (!BJGameMode) return;
	BJGameMode->PlayerStand();
}

void UGameHUDWidget::OnStartRound()
{
	SetElementVisibility(true);
}

void UGameHUDWidget::OnEndRound(EEndState EndState)
{
	checkf(EndTexts.Contains(EndState) && EndTextsColor.Contains(EndState), TEXT("No Text or Color for EndState. Check Widget!!!"));
	ResultText->SetText(EndTexts[EndState]);
	ResultText->SetColorAndOpacity(EndTextsColor[EndState]);
	SetElementVisibility(false);
}

void UGameHUDWidget::SetElementVisibility(bool bIsStart) const 
{
	ResultText->SetVisibility(bIsStart ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	StartButton->SetVisibility(bIsStart ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	HitButton->SetVisibility(bIsStart ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	StandButton->SetVisibility(bIsStart ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

int32 UGameHUDWidget::GetPlayerTotal() const
{
	if (!BJGameMode) return 0;
	return BJGameMode->GetPlayerTotal();
}

int32 UGameHUDWidget::GetDealerTotal() const
{
	if (!BJGameMode) return 0;
	return BJGameMode->GetDealerTotal();
}
