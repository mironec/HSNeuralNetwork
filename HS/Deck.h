#pragma once
#include "CardContainer.h"
#include "Card.h"
#include <random>
#include <exception>

#define MAX_DECK_SIZE 256

class Deck : public CardContainer
{
public:
	class EmptyDeckException : public std::exception {

	};
	Deck();
	Deck(Deck &deckToCopy);
	~Deck();
	Card * drawRandomCard(std::mt19937_64& randomNumberGenerator);
	bool checkAdding(Card * card);
};

