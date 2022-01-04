#pragma once

#include "BJTypes.generated.h"

/** Offset between cards in deck on level */
constexpr float ZOffsetBetweenCards = 0.3f;

/** Order of elements depending on Card's Texture */
UENUM(BlueprintType)
enum class ESuit : uint8
{
	EST_Clubs UMETA(DisplayName = "Clubs"),
	EST_Hearts UMETA(DisplayName = "Hearts"),
	EST_Spades UMETA(DisplayName = "Spades"),
	EST_Diamonds UMETA(DisplayName = "Diamonds"),
	EST_MAX UMETA(DisplayName = "DefaultMAX")
};

/** Order of elements depending on Card's Texture */
UENUM(Blueprinttype)
enum class ERank : uint8
{
	ERT_Ace UMETA(DisplayName = "Ace"),
	ERT_2 UMETA(DisplayName = "2"),
	ERT_3 UMETA(DisplayName = "3"),
	ERT_4 UMETA(DisplayName = "4"),
	ERT_5 UMETA(DisplayName = "5"),
	ERT_6 UMETA(DisplayName = "6"),
	ERT_7 UMETA(DisplayName = "7"),
	ERT_8 UMETA(DisplayName = "8"),
	ERT_9 UMETA(DisplayName = "9"),
	ERT_10 UMETA(DisplayName = "10"),
	ERT_Jack UMETA(DisplayName = "Jack"),
	ERT_Queen UMETA(DisplayName = "Queen"),
	ERT_King UMETA(DisplayName = "King"),
	ERT_MAX UMETA(DisplayName = "DefaultMAX")
};


/** Round End States */
UENUM(BlueprintType)
enum class EEndState : uint8
{
	EES_PlayerWins UMETA(DisplayName = "PlayerWins"),
	EES_DealerWins UMETA(DisplayName = "DealerWins"),
	EES_Tie UMETA(DisplayName = "Tie"),
	EES_MAX UMETA(DisplayName = "DefaultMAX")
};
