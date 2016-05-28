#include "stdafx.h"
#include "Hero.h"


Hero::Hero(HeroType * heroType)
{
	this->cardType = nullptr;
	this->originalAttack = this->attack = 0;
	this->originalHealth = this->health = this->maxHealth = heroType->getMaxHP();
	this->originalManaCost = this->manaCost = 0;

	this->name = std::string("");
	this->tags = CardTag::hero;

	this->heroType = heroType;
	this->exhausted = false;
}


Hero::~Hero()
{
}
