#pragma once
#include <memory>
#include <exception>
#include "Card.h"
#include "CardContainer.h"

#define MAX_HAND_SIZE 10

class Hand : public CardContainer
{
public:
	Hand();
	~Hand();

	bool checkAdding(Card * card);
};

