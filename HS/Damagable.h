#pragma once
#include <cstdint>

class Damagable
{
protected:
	int32_t health;
	int32_t maxHealth;
public:
	Damagable();
	~Damagable();
	virtual void takeDamage(int32_t howMuch) = 0;
	int32_t getHealth();
	int32_t getMaxHealth();
};

