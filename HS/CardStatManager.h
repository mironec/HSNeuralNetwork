#pragma once
#include <string>
#include <vector>
#include <exception>
#include "CardType.h"
#include "Card.h"

class CardStatManager
{
private:
	static CardStatManager * instance;
	static std::vector<CardType*> cardTypes;
public:
	class CardStatManagerAlreadyExistsException : public std::exception {};
	CardStatManager();
	~CardStatManager();

	static CardType * getCardType(std::string fromCardName);
	static Card * createDeckCardFromName(std::string fromCardName);
};

