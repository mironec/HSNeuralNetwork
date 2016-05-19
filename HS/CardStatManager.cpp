#include "stdafx.h"
#include "CardStatManager.h"

std::vector<CardType*> CardStatManager::cardTypes(0);
CardStatManager * CardStatManager::instance = nullptr;

CardStatManager::CardStatManager()
{
	if (instance == nullptr) instance = this;
	else throw CardStatManagerAlreadyExistsException();

	cardTypes.push_back(new CardType(3, 2, "Bloodfen Raptor", 2)); cardTypes[0]->setTags(CardTag::minion | CardTag::beast);
	cardTypes.push_back(new CardType(2, 3, "River Crocolisk", 2)); cardTypes[1]->setTags(CardTag::minion | CardTag::beast);
	cardTypes.push_back(new CardType(0, 0, "The Coin", 0)); cardTypes[2]->setTags(CardTag::spell);
}


CardStatManager::~CardStatManager()
{
	instance = nullptr;
}

CardType * CardStatManager::getCardType(std::string fromCardName)
{
	CardType * toReturn = nullptr;
	for (size_t i = 0;i < cardTypes.size();i++) {
		if (cardTypes[i]->getName().compare(fromCardName) == 0) {
			toReturn = cardTypes[i];
			break;
		}
	}
	return toReturn;
}

Card * CardStatManager::createDeckCardFromName(std::string fromCardName)
{
	CardType * parent = getCardType(fromCardName);
	Card * child = new Card(parent);
	return child;
}
