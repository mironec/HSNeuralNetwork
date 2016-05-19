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
	int8_t numCards;
public:
	class CardIndexOutOfBoundsException : public std::exception {

	};
	class CardContainerFullException : public std::exception {};

	CardContainer();
	~CardContainer();

	virtual bool checkAdding(Card * card) = 0;

	void addCardToEnd(Card * card);
	void addCard(Card * card, int8_t pos = 0);
	Card * removeCard(int8_t pos);
	Card * getCard(int8_t pos);
	std::vector<Card*> getCards();
	int8_t getNumberOfCards();
};

