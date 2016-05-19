#pragma once
#include <memory>
#include "Card.h"
#include "CardContainer.h"

#define MAX_BOARD_SIZE 7

class Board : public CardContainer
{
public:
	Board();
	~Board();

	bool checkAdding(Card * card);
};

