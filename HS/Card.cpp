#include "stdafx.h"
#include "Card.h"


Card::Card(CardType * cardType)
{
	this->cardType = cardType;
	this->originalAttack = this->attack = cardType->getAttack();
	this->originalHealth = this->health = cardType->getHealth();
	this->originalManaCost = this->manaCost = cardType->getManaCost();
	this->name = std::string(cardType->getName());
	this->tags = cardType->getTags();
}


Card::~Card()
{
}

std::string Card::getName()
{
	return name;
}

bool Card::getTag(CardTag flag) {
	return (tags & flag) != 0;
}

CardTag Card::getTags()
{
	return tags;
}

int32_t Card::getManaCost()
{
	return manaCost;
}
