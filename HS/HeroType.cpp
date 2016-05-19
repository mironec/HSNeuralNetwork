#include "stdafx.h"
#include "HeroType.h"


HeroType::HeroType()
{
}

HeroType::HeroType(int32_t maxHP): maxHP(maxHP)
{
}


HeroType::~HeroType()
{
}

int32_t HeroType::getMaxHP() {
	return maxHP;
}

HeroType HeroType::JAINA(30);
