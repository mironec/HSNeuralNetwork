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
	if (!checkAdding(card)) throw CardContainerFullException();
	CardNode * newCardNode = new CardNode();
	newCardNode->card = card;
	newCardNode->next = nullptr;
	newCardNode->prev = endCards;

	if (endCards == nullptr) {
		cards = newCardNode;
	}
	else {
		endCards->next = newCardNode;
	}

	endCards = newCardNode;
	numCards++;
}

void CardContainer::addCard(Card * card, int8_t pos)
{
	if (!checkAdding(card)) throw CardContainerFullException();
	if (pos >= numCards+1 || pos < 0) throw CardIndexOutOfBoundsException();

	CardNode * newCardNode = new CardNode();
	newCardNode->card = card;
	newCardNode->next = nullptr;
	newCardNode->prev = nullptr;

	CardNode * current = cards;
	for (int i = 0;i < pos;i++) {
		current = current->next;
	}

	if (current == nullptr) {			//Adding to the end of the list
		addCardToEnd(card);
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

Card * CardContainer::removeCard(int8_t pos)
{
	if (pos >= numCards || pos < 0) throw CardIndexOutOfBoundsException();

	CardNode * current = cards;

	for (int i = 0;i < pos;i++) {
		current = current->next;
	}

	Card * toReturn = current->card;
	if (current->prev != nullptr) current->prev->next = current->next;
	else cards = current->next;
	if (current->next != nullptr) current->next->prev = current->prev;
	else endCards = current->prev;
	numCards--;

	delete current;

	return toReturn;
}

Card * CardContainer::getCard(int8_t pos)
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

int8_t CardContainer::getNumberOfCards()
{
	return numCards;
}
