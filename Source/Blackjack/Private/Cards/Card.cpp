// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Card.h"


ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardMesh"));
	CardMesh->SetupAttachment(GetRootComponent());
}

void ACard::InitCard(const ERank Rank, const ESuit Suit)
{
	CardRank = Rank;
	CardSuit = Suit;

	/**
	 * Set material offset in depending on Suit and Rank.
	 * Get Enum index of Rank(Suit) and Set it to material.
	 * See material M_CardFront & texture.
	 */ 
	const auto MaterialInst = CardMesh->CreateAndSetMaterialInstanceDynamic(1);
	if (!MaterialInst) return;
	const int32 RankIndex = static_cast<int32>(Rank);
	const int32 SuitIndex = static_cast<int32>(Suit);
	MaterialInst->SetScalarParameterValue("RankNum", RankIndex);
	MaterialInst->SetScalarParameterValue("SuitNum", SuitIndex);
}

int32 ACard::GetCardValue() const
{
	switch (CardRank)
	{
	case ERank::ERT_Ace: return 11; break;
	case ERank::ERT_2: return 2; break;
	case ERank::ERT_3: return 3; break;
	case ERank::ERT_4: return 4; break;
	case ERank::ERT_5: return 5; break;
	case ERank::ERT_6: return 6; break;
	case ERank::ERT_7: return 7; break;
	case ERank::ERT_8: return 8; break;
	case ERank::ERT_9: return 9; break;
	case ERank::ERT_10: 
	case ERank::ERT_Jack: 
	case ERank::ERT_Queen: 
	case ERank::ERT_King: return 10; break;
	default: return 0;
	}
	return 0;
}

void ACard::MoveCard_Implementation(FVector NewLocation)
{

}

