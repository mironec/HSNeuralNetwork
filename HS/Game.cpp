#include "stdafx.h"
#include "Game.h"


Game::Game(Deck &p1Deck, Deck &p2Deck, HeroType &p1HT, HeroType &p2HT, Card * coinCard)
{
	player1 = std::make_unique<Player>(this, randomGen, p1Deck, p1HT);
	player2 = std::make_unique<Player>(this, randomGen, p2Deck, p2HT);

	randomGen.seed(time(NULL));

	if (randomGen() % 2 == 0) currentPlayer = firstPlayer = 1;
	else currentPlayer = firstPlayer = 2;

	getPlayer(1)->mulligan(firstPlayer == 1, coinCard);
	getPlayer(2)->mulligan(firstPlayer == 2, coinCard);

	setExpectingCommand(getCurrentPlayer()->isExpectingCommand());
	setExpectedCommandType(getCurrentPlayer()->getExpectedCommandType());
}

Player * Game::getCurrentPlayer() {
	return getPlayer(currentPlayer);
}

int8_t Game::getCurrentPlayerID()
{
	return currentPlayer;
}

void Game::receiveCommand(const std::shared_ptr<Command> &command) {
	if (!isExpectingCommand()) throw Command::WrongCommandException(command);
	getCurrentPlayer()->receiveCommand(command);
	if (!getCurrentPlayer()->isExpectingCommand()) { currentPlayer = (currentPlayer % 2) + 1; getCurrentPlayer()->startTurn(); }
	setExpectingCommand(getCurrentPlayer()->isExpectingCommand());
	setExpectedCommandType(getCurrentPlayer()->getExpectedCommandType());
}

Player * Game::getPlayer(int8_t id) {
	switch (id) {
	case 1:
		return player1.get();
	case 2:
		return player2.get();
	default:
		return nullptr;
	}
}

void Game::playCard(Card* card, int arg, ...) {
	va_list ap;
	va_start(ap, arg);

	if (card->getTag(CardTag::minion)) {
		try {
			getCurrentPlayer()->spendMana(card->getManaCost());
			getCurrentPlayer()->getBoard()->addCard(card, arg);
			getCurrentPlayer()->getHand()->removeCard(va_arg(ap, int));
		}
		catch (const CardContainer::CardContainerFullException &e) {
			(void)e;
			getCurrentPlayer()->refundMana(card->getManaCost());
		}
	}

	va_end(ap);
}

void Game::dealDamage(Damagable &target, Damagable &source, Player &sourcePlayer, int32_t howMuch) {
	target.takeDamage(howMuch);
}


Game::~Game()
{
}
