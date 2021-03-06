#pragma once
#include <cstdint>
#include <string>

enum class CardTag : int32_t {
	minion = 1 << 0,
	spell = 1 << 1,
	beast = 1 << 2,
	noTarget = 1 << 3,
	hero = 1 << 4
};

CardTag operator|(CardTag a, CardTag b);
CardTag operator&(CardTag a, CardTag b);
CardTag operator~(CardTag a);
bool operator==(CardTag a, int32_t b);
bool operator!=(CardTag a, int32_t b);

class CardType
{
private:
	int32_t attack;
	int32_t health;
	int32_t manaCost;

	CardTag tags;

	std::string name;
public:
	CardType();
	CardType(int32_t attack, int32_t health, std::string, int32_t manaCost);
	~CardType();
	int32_t getAttack();
	int32_t getHealth();
	std::string getName();
	int32_t getManaCost();

	void setTag(CardTag tag, bool value);
	void setTags(CardTag tags);
	CardTag getTags();
	bool getTag(CardTag flag);
};
