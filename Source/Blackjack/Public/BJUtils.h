#pragma once

#include "Cards/Card.h"

namespace Utils
{

	/** Destroy all ACards in TArray. */
	static void ClearDeck(TArray<ACard*> &Deck)
	{
		if (Deck.Num() <= 0) return;
		for (const auto Card : Deck)
		{
			if (Card)
			{
				Card->Destroy();
			}
		}
		Deck.Empty();
	}


	
}
