// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BJTypes.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDWidget.generated.h"



UCLASS()
class BLACKJACK_API UGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="End State")
	TMap<EEndState, FText> EndTexts;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="End State")
	TMap<EEndState, FLinearColor> EndTextsColor;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResultText;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HitButton;
	UPROPERTY(meta = (BindWidget))
	UButton* StandButton;

private:
	UPROPERTY()
	class ABJGameMode* BJGameMode = nullptr;
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable, Category= "UI")
	int32 GetPlayerTotal() const;
	UFUNCTION(BlueprintCallable, Category= "UI")
	int32 GetDealerTotal() const;

private:
	UFUNCTION()
	void OnStartButtonPressed();
	UFUNCTION()
	void OnHitButtonPressed();
	UFUNCTION()
	void OnStandButtonPressed();

	void OnStartRound();
	void OnEndRound(EEndState EndState);

	void SetElementVisibility(bool bIsStart) const;
};

