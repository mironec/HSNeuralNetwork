#include "stdafx.h"
#include "CardContainer.h"

CardContainer::CardContainer()
{
	cards = nullptr;
	endCards = nullptr;
	numCards = 0;
}


CardContainer::~CardContainer()
{
}

void CardContainer::addCardToEnd(Card * card)
{
	addCardInternal(card, numCards);
}

void CardContainer::addCard(Card * card, int32_t position) {
	addCardInternal(card, position);
}

void CardContainer::addCardInternal(Card * card, int32_t position)
{
	if (!checkAdding(card)) throw CardContainerFullException();
	if (position > numCards || position < 0) throw CardIndexOutOfBoundsException();

	CardNode * newCardNode = new CardNode();
	newCardNode->card = card;
	newCardNode->next = nullptr;
	newCardNode->prev = nullptr;

	CardNode * current = cards;
	if (position == numCards) current = endCards;
	else {
		for (int i = 0;i < position;i++) {
			current = current->next;
		}
	}

	if (current == nullptr) {			//Adding to the end of the list
		if (endCards == nullptr)
			cards = newCardNode;
		else
			endCards->next = newCardNode;
		newCardNode->prev = endCards;
		endCards = newCardNode;
		numCards++;
		return;
	}
	if (current->prev == nullptr) {		//Adding to the front of the list
		cards = newCardNode;
		newCardNode->next = current;
		current->prev = newCardNode;
		numCards++;
		return;
	}

	current->prev->next = newCardNode;
	newCardNode->prev = current->prev;
	newCardNode->next = current;
	current->prev = newCardNode;
	numCards++;
}

Card * CardContainer::removeCard(CardNode * cardNode)
{
	Card * toReturn = cardNode->card;
	if (cardNode->prev != nullptr) cardNode->prev->next = cardNode->next;
	else cards = cardNode->next;
	if (cardNode->next != nullptr) cardNode->next->prev = cardNode->prev;
	else endCards = cardNode->prev;
	numCards--;

	delete cardNode;

	return toReturn;
}

Card * CardContainer::removeCard(int32_t pos)
{
	if (pos >= numCards || pos < 0) throw CardIndexOutOfBoundsException();

	CardNode * current = cards;

	for (int i = 0;i < pos;i++) {
		current = current->next;
	}

	return removeCard(current);
}

Card * CardContainer::removeCard(Card * card)
{
	CardNode * current = cards;

	while (current != nullptr) {
		if (current->card == card) break;
		current = current->next;
	}

	if (current == nullptr) throw CardIndexOutOfBoundsException();

	return removeCard(current);
}

Card * CardContainer::getCard(int32_t pos)
{
	if (pos >= numCards || pos < 0) throw CardIndexOutOfBoundsException();

	CardNode * current = cards;

	for (int i = 0;i < pos;i++) {
		current = current->next;
	}

	return current->card;
}

std::vector<Card*> CardContainer::getCards()
{
	std::vector<Card*> v;

	CardNode * current = cards;
	while (current != nullptr) {
		v.push_back(current->card);
		current = current->next;
	}

	return v;
}

int32_t CardContainer::getNumberOfCards()
{
	return numCards;
}
