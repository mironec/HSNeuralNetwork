#include "stdafx.h"
#include "CardType.h"

CardType::CardType(int32_t attack, int32_t health, std::string name, int32_t manaCost):
	attack(attack), health(health), name(name), manaCost(manaCost)
{
	tags = static_cast<CardTag>(0);
}

CardType::~CardType()
{
}

int32_t CardType::getAttack()
{
	return attack;
}

int32_t CardType::getHealth()
{
	return health;
}

std::string CardType::getName()
{
	return name;
}

int32_t CardType::getManaCost()
{
	return manaCost;
}

void CardType::setTag(CardTag tag, bool value)
{
	if (value) tags = tags | tag;
	else tags = tags & ~tag;
}

void CardType::setTags(CardTag tags)
{
	this->tags = tags;
}

CardTag CardType::getTags()
{
	return tags;
}

CardTag operator~(CardTag a)
{
	return static_cast<CardTag>(~static_cast<int>(a));
}

CardTag operator|(CardTag a, CardTag b)
{
	return static_cast<CardTag>(static_cast<int>(a) | static_cast<int>(b));
}

CardTag operator&(CardTag a, CardTag b)
{
	return static_cast<CardTag>(static_cast<int>(a) & static_cast<int>(b));
}

bool operator==(CardTag a, unsigned int b)
{
	return static_cast<int>(a)==b;
}

bool operator!=(CardTag a, unsigned int b)
{
	return static_cast<int>(a)!=b;
}
