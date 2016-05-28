#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <cstdarg>
#include "ForwardDeclaration.h"
#include "CardType.h"
#include "Damagable.h"

class Card : public Damagable {
protected:
	std::string name;
	int32_t attack;
	int32_t originalAttack;
	int32_t originalHealth;
	int32_t manaCost;
	int32_t originalManaCost;
	bool exhausted;
	int32_t orderId;

	CardTag tags;

	CardType * cardType;
public:
	Card();
	Card(CardType* prototypeCardType, int32_t orderId);
	~Card();
	std::string getName();
	CardTag getTags();
	int32_t getManaCost();
	int32_t getAttack();
	int32_t getOrder();
	void setOrder(int32_t orderId);
	bool isExhausted();
	bool getTag(CardTag flag);
	void takeDamage(int32_t howMuch);
};
