#pragma once
#include <cstdint>

class HeroType
{
private:
	int32_t maxHP;
public:
	HeroType();
	HeroType(int32_t maxHP);
	~HeroType();
	int32_t getMaxHP();

	static HeroType JAINA;
};
