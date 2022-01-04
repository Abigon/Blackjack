// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BJTypes.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

UCLASS()
class BLACKJACK_API ACard : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CardMesh;
	
public:	
	ACard();

	/** Set Rank & Suit of card. Also set texture's offset. Use this function after SpawnActor */
	void InitCard(const ERank Rank, const ESuit Suit);

	/** Get value of card's rank in point */
	int32 GetCardValue() const;

protected:
	/** Move card's actor to new location in World */ 
	UFUNCTION(BlueprintNativeEvent, Category = "Card")
	void MoveCard(FVector NewLocation);

private:
	ERank CardRank = ERank::ERT_Ace;
	ESuit CardSuit = ESuit::EST_Clubs;

};
