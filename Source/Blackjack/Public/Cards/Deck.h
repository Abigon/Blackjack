// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Deck.generated.h"

UCLASS()
class BLACKJACK_API ADeck : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Deck")
	TSubclassOf<class ACard> CardClass = nullptr;
	
private:
	TArray<class ACard*> CardsDeck;
	
public:	
	ADeck();

	void CreateShuffledDeck();

	/** Get last card in deck and remove this card from deck */
	ACard* GetCardOnTop();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void CreateDeck();
	void ShuffleDeck();
	void ClearDeck();
	
	/** Spawn new card in World without InitCard */
	ACard* SpawnCard();

	/** Set world location in array order for Z-axis */ 
	void FixZOffset();
};
