#pragma once
#include <cstdint>
#include "HeroType.h"
#include "Card.h"
#include "CardType.h"

class Hero : public Card
{
private:
	HeroType * heroType;
public:
	Hero(HeroType*);
	~Hero();
};

