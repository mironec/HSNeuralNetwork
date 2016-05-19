#include "stdafx.h"
#include "Hero.h"


Hero::Hero(HeroType * heroType)
{
	this->heroType = heroType;
	this->health = this->maxHealth = heroType->getMaxHP();
}


Hero::~Hero()
{
}

void Hero::takeDamage(int32_t howMuch) {
	health -= howMuch;
}
