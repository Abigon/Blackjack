// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Deck.h"
#include "BJUtils.h"
#include "Cards/Card.h"


ADeck::ADeck()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADeck::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearDeck();
	Super::EndPlay(EndPlayReason);
}

void ADeck::CreateDeck()
{
	ClearDeck();

	/** Spawn and Init Cards and Add them to Deck's array in two loops */ 
	for (int32 SuitIndex = 0; SuitIndex < StaticEnum<ESuit>()->NumEnums() - 1; SuitIndex++) 
	{                                                                          
		const ESuit SuitElem = static_cast<ESuit>(SuitIndex);
		for (int32 RankIndex = 0; RankIndex < StaticEnum<ERank>()->NumEnums() - 1; RankIndex++)
		{
			const ERank RankElem = static_cast<ERank>(RankIndex);

			const auto Card = SpawnCard();
			if (Card)
			{
				Card->InitCard(RankElem, SuitElem);
				CardsDeck.Add(Card);
			}
		}
	}
	FixZOffset();
}

ACard* ADeck::SpawnCard()  
{
	const FRotator CardRotation = FRotator(180.f, 0.f, 0.f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	const auto Card = GetWorld()->SpawnActor<ACard>(CardClass, GetActorLocation(), CardRotation, SpawnParams);
	return Card;
}

void ADeck::ClearDeck()
{
	Utils::ClearDeck(CardsDeck);
}

void ADeck::ShuffleDeck()
{
	if (CardsDeck.Num() <=0) return;
	int32 CountToShuffle = CardsDeck.Num();
	do
	{
		const int32 CardIndex = FMath::RandRange(0, CountToShuffle - 1);
		ACard* TempCard = CardsDeck[CardIndex];
		CardsDeck.Add(TempCard);
		CardsDeck.RemoveAt(CardIndex);
		CountToShuffle--;
	}
	while (CountToShuffle > 1);
	FixZOffset();
}

void ADeck::FixZOffset()
{
	if (CardsDeck.Num() <=0) return;
	FVector NextCardLocation = GetActorLocation();
	for (const auto Card : CardsDeck)
	{
		if (Card)
		{
			NextCardLocation.Z += ZOffsetBetweenCards;
			Card->SetActorLocation(NextCardLocation);
		}
	}
}

ACard* ADeck::GetCardOnTop() 
{
	if (CardsDeck.Num() <=0) return nullptr;
	ACard* TempCard = CardsDeck.Last();
	CardsDeck.Remove(TempCard);
	return TempCard;
}

void ADeck::CreateShuffledDeck()
{
	CreateDeck();
	ShuffleDeck();
}
