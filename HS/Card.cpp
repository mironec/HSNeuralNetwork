#include "stdafx.h"
#include "Card.h"


Card::Card()
{
}

Card::Card(CardType * cardType, int32_t orderId): orderId(orderId)
{
	this->cardType = cardType;
	this->originalAttack = this->attack = cardType->getAttack();
	this->originalHealth = this->maxHealth = this->health = cardType->getHealth();
	this->originalManaCost = this->manaCost = cardType->getManaCost();
	this->name = std::string(cardType->getName());
	this->tags = cardType->getTags();
	this->exhausted = true;
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

void Card::takeDamage(int32_t howMuch) {
	health -= howMuch;
}

CardTag Card::getTags()
{
	return tags;
}

int32_t Card::getManaCost()
{
	return manaCost;
}

int32_t Card::getAttack()
{
	return attack;
}

int32_t Card::getOrder()
{
	return orderId;
}

void Card::setOrder(int32_t orderId)
{
	this->orderId = orderId;
}

bool Card::isExhausted()
{
	return exhausted;
}
