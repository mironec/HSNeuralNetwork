#pragma once
#include "Hero.h"
#include "Hand.h"
#include "Deck.h"
#include "Command.h"
#include "Commandable.h"
#include "Game.h"
#include "Board.h"
#include "Card.h"
#include <memory>
#include <random>
#include <vector>
#include "GameplayNotAllowedException.h"

class Player : public Commandable
{
private:
	std::unique_ptr<Hero> hero;
	std::unique_ptr<Hand> hand;
	std::unique_ptr<Deck> deck;
	std::unique_ptr<Board> board;
	std::mt19937_64 * randomGen;
	std::vector<Card*> options;
	std::vector<std::shared_ptr<Command>> commands;
	Card * pickedCard;
	Game * game;
	int8_t mana;
	int8_t maxMana;
	int8_t currentOverload;
	int8_t nextOverload;
	int8_t fatigueDamage;
	bool inMulligan;
public:
	class NotEnoughManaException : public GameplayNotAllowedException {
		std::string report() const;
		const char * what() const;
	};
	Player(Game * game, std::mt19937_64& randomNumberGenerator, Deck &deckToCopy, HeroType &heroType);
	~Player();
	void receiveCommand(const std::shared_ptr<Command> &command);
	std::vector<Card*> getCardChoices();
	Hand * getHand() const;
	Board * getBoard() const;
	Hero * getHero() const;
	int8_t getFreeMana();
	int8_t getMaxMana();
	void spendMana(int8_t howMuch);
	void refundMana(int8_t howMuch);
	void mulligan(bool isFirst, Card * coinCard);
	void resolveMulligan(Card * coinCard);
	void endTurn();
	void startTurn();
	void resolvePlays();
	void resolvePlay(const std::shared_ptr<Command> &command);
};

