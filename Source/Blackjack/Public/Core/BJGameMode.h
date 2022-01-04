// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BJTypes.h"
#include "GameFramework/GameModeBase.h"
#include "BJGameMode.generated.h"



DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoundEndSignature, EEndState);
DECLARE_MULTICAST_DELEGATE(FOnRoundStartSignature);

UCLASS()
class BLACKJACK_API ABJGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	FOnRoundEndSignature OnRoundEnd;
	FOnRoundStartSignature OnRoundStart;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Desk")
	FVector StartPlayerCardsPosition = {-170.f, 0.f, 80.f};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Desk")
	FVector StartDealerCardsPosition = {200.f, 0.f, 80.f};

	/** Y-axis offset for next card in player's and dealer's decks  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Desk")
	float CardsYOffset = 50.f;
	
private:
	/** TimerHandle for delay between dealer's hits */
	FTimerHandle DealerHitTimerHande;
	
	TArray<class ACard*> PlayerCards;
	TArray<ACard*> DealerCards;

	UPROPERTY()
	class ADeck* MainDeck = nullptr;

	FVector NextPlayerCardPosition;
	FVector NextDealerCardPosition;

	int32 PlayerTotal = 0;
	int32 DealerTotal = 0;
	
public:
	virtual void StartPlay() override;
	
	void StartRound();
	void PlayerHit();
	void PlayerStand();

	int32 GetPlayerTotal() const { return PlayerTotal; }
	int32 GetDealerTotal() const { return DealerTotal; }

private:
	void EndRound(const EEndState State); 
	void ClearDecks();

	void PlayerTakeCard(ACard* Card);
	void DealerTakeCard(ACard* Card);
	void DealerHit();
};
