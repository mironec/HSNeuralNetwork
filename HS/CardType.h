#pragma once
#include <cstdint>
#include <string>

enum class CardTag {
	minion = 1 << 0,
	spell = 1 << 1,
	beast = 1 << 2
};

CardTag operator|(CardTag a, CardTag b);
CardTag operator&(CardTag a, CardTag b);
CardTag operator~(CardTag a);
bool operator==(CardTag a, unsigned int b);
bool operator!=(CardTag a, unsigned int b);

class CardType
{
private:
	int32_t attack;
	int32_t health;
	int32_t manaCost;

	CardTag tags;

	std::string name;
public:
	CardType(int32_t attack, int32_t health, std::string, int32_t manaCost);
	~CardType();
	int32_t getAttack();
	int32_t getHealth();
	std::string getName();
	int32_t getManaCost();

	void setTag(CardTag tag, bool value);
	void setTags(CardTag tags);
	CardTag getTags();
};
