#pragma once
#include <memory>
#include <vector>
#include "Card.h"

class Card;

class CardContainer
{
protected:
	class CardNode {
	public:
		Card * card;
		CardNode * next;
		CardNode * prev;
	};
	CardNode * cards;
	CardNode * endCards;
	int32_t numCards;
	Card * removeCard(CardNode * cardNode);
public:
	class CardIndexOutOfBoundsException : public std::exception {

	};
	class CardContainerFullException : public std::exception {};

	CardContainer();
	~CardContainer();

	virtual bool checkAdding(Card * card) = 0;

	void addCardToEnd(Card * card);
	void addCard(Card * card, int32_t pos = 0);
	void addCardInternal(Card * card, int32_t pos = 0);
	Card * removeCard(int32_t pos);
	Card * removeCard(Card * card);
	Card * getCard(int32_t pos);
	std::vector<Card*> getCards();
	int32_t getNumberOfCards();
};

