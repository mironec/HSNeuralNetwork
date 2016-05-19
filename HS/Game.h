#pragma once
#include <memory>
#include <random>
#include <ctime>
#include "Player.h"
#include "Deck.h"
#include "CardType.h"
#include "Commandable.h"

class Player;

class Game : public Commandable
{
private:
	std::unique_ptr<Player> player1, player2;
	std::mt19937_64 randomGen;
	int8_t currentPlayer;
	int8_t firstPlayer;
public:
	Game(Deck &player1Deck, Deck &player2Deck, HeroType &player1HeroType, HeroType &player2HeroType, Card * coinCard);
	~Game();
	Player * getCurrentPlayer();
	int8_t getCurrentPlayerID();
	Player * getPlayer(int8_t id);
	void receiveCommand(const std::shared_ptr<Command> &command);
	void playCard(Card* card, int arg, ...);
	void dealDamage(Damagable &target, Damagable &source, Player &sourcePlayer, int32_t howMuch);
};

