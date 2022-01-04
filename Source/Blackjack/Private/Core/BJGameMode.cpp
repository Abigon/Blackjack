// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BJGameMode.h"
#include "Cards/Card.h"
#include "Cards/Deck.h"
#include "BJUtils.h"
#include "Kismet/GameplayStatics.h"

void ABJGameMode::StartPlay()
{
	Super::StartPlay();

	/** Find ADeck in World and save its pointer to variable */ 
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADeck::StaticClass(), TempActors);
	checkf(TempActors.Num() > 0, TEXT("Missing Deck on level!!!"));
	MainDeck = Cast<ADeck>(TempActors[0]);
}

/** Set all default values and deal one card for player and one card for dealer */ 
void ABJGameMode::StartRound()
{
	if (!MainDeck) return;
	ClearDecks();
	NextPlayerCardPosition = StartPlayerCardsPosition;
	NextDealerCardPosition = StartDealerCardsPosition;
	PlayerTotal = 0;
	DealerTotal = 0;
	MainDeck->CreateShuffledDeck();

	PlayerHit();
	DealerHit();

	OnRoundStart.Broadcast();
}

void ABJGameMode::EndRound(const EEndState State)
{
	GetWorldTimerManager().ClearTimer(DealerHitTimerHande);
	OnRoundEnd.Broadcast(State);
}

/** Deal card to player and check player's total for win or lose */
void ABJGameMode::PlayerHit()
{
	if (!MainDeck) return;
	PlayerTakeCard(MainDeck->GetCardOnTop());
	if (PlayerTotal == 21)
	{
		EndRound(EEndState::EES_PlayerWins);
	}
	else if (PlayerTotal > 21)
	{
		EndRound(EEndState::EES_DealerWins);
	}
}

/** When player stand StartTimer for dealer hits */
void ABJGameMode::PlayerStand()
{
	GetWorldTimerManager().SetTimer(DealerHitTimerHande, this, &ABJGameMode::DealerHit, 1.f, true, 0.1f);
}

/** Deal card to dealer and check dealer's total for win or lose */
void ABJGameMode::DealerHit()
{
	if (!MainDeck) return;
	DealerTakeCard(MainDeck->GetCardOnTop());
	if (DealerTotal == 21)
	{
		EndRound(EEndState::EES_DealerWins);
	}
	else if (DealerTotal > 21)
	{
		EndRound(EEndState::EES_PlayerWins);
	}
	else if (DealerTotal > 16)
	{
		if (DealerTotal == PlayerTotal)
		{
			EndRound(EEndState::EES_Tie);
		}
		else if (DealerTotal > PlayerTotal)
		{
			EndRound(EEndState::EES_DealerWins);
		}
		else
		{
			EndRound(EEndState::EES_PlayerWins);
		}
	}
}

void ABJGameMode::ClearDecks()
{
	Utils::ClearDeck(PlayerCards);
	Utils::ClearDeck(DealerCards);
}

/** Player take new card and calculate player's total without check */
void ABJGameMode::PlayerTakeCard(ACard* Card)
{
	if (!Card) return;
	PlayerCards.Add(Card);
	PlayerTotal += Card->GetCardValue();
	Card->MoveCard_Implementation(NextPlayerCardPosition);
	NextPlayerCardPosition.Y += CardsYOffset;
	NextPlayerCardPosition.Z += ZOffsetBetweenCards;
}

/** Dealer take new card and calculate dealer's total without check */
void ABJGameMode::DealerTakeCard(ACard* Card)
{
	if (!Card) return;
	DealerCards.Add(Card);
	DealerTotal += Card->GetCardValue();
	Card->MoveCard_Implementation(NextDealerCardPosition);
	NextDealerCardPosition.Y += CardsYOffset;
	NextDealerCardPosition.Z += ZOffsetBetweenCards;
}
