#pragma once
#include <cstdint>
#include "HeroType.h"
#include "Damagable.h"

class Hero : public Damagable
{
private:
	HeroType * heroType;
public:
	Hero(HeroType*);
	~Hero();
	void takeDamage(int32_t howMuch);
};

