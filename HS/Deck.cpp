#include "stdafx.h"
#include "Deck.h"


Deck::Deck()
{
}

Deck::Deck(Deck &deck) {
	for (int i = 0;i < deck.getNumberOfCards();i++)
		this->addCardToEnd(deck.getCard(i));
}

Deck::~Deck()
{
}

Card * Deck::drawRandomCard(std::mt19937_64 &generator)
{
	if (numCards == 0) throw EmptyDeckException();

	Card * toDraw = nullptr;
	int32_t num = generator()%numCards;

	toDraw = removeCard(num);

	return toDraw;
}

bool Deck::checkAdding(Card * card)
{
	return numCards < MAX_DECK_SIZE;
}
