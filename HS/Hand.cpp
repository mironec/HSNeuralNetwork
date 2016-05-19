#include "stdafx.h"
#include "Hand.h"


Hand::Hand()
{
}

Hand::~Hand()
{
}

bool Hand::checkAdding(Card * card)
{
	return numCards < MAX_HAND_SIZE;
}
