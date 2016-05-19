#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <cstdarg>
#include "ForwardDeclaration.h"
#include "CardType.h"

class Card {
private:
	std::string name;
	int32_t attack;
	int32_t originalAttack;
	int32_t health;
	int32_t originalHealth;
	int32_t manaCost;
	int32_t originalManaCost;

	CardTag tags;

	CardType * cardType;
public:
	Card(CardType* prototypeCardType);
	~Card();
	std::string getName();
	CardTag getTags();
	int32_t getManaCost();
	bool getTag(CardTag flag);
};

