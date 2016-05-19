#include "stdafx.h"
#include "Board.h"


Board::Board()
{
}


Board::~Board()
{
}

bool Board::checkAdding(Card * card)
{
	return numCards < MAX_BOARD_SIZE;
}
