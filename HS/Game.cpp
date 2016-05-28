#include "stdafx.h"
#include "Game.h"


Game::Game(Deck &p1Deck, Deck &p2Deck, HeroType &p1HT, HeroType &p2HT, Card * coinCard)
{
	player1 = std::make_unique<Player>(this, randomGen, p1Deck, p1HT);
	player2 = std::make_unique<Player>(this, randomGen, p2Deck, p2HT);

	randomGen.seed(time(NULL));

	if (randomGen() % 2 == 0) currentPlayer = firstPlayer = 1;
	else currentPlayer = firstPlayer = 2;
	gameFlags = 0;
	order = 0;

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

int8_t Game::getGameFlags()
{
	return gameFlags;
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
			card->setOrder(order++);
		}
		catch (const CardContainer::CardContainerFullException &e) {
			(void)e;
			getCurrentPlayer()->refundMana(card->getManaCost());
		}
	}

	va_end(ap);
}

void Game::minionAttack(Card * source, Card * target)
{
	target->takeDamage(source->getAttack());
	source->takeDamage(target->getAttack());

	processDeaths();
}

void Game::minionDeath(Card * minion) {
	try {
		player1->getBoard()->removeCard(minion);
	}
	catch (CardContainer::CardIndexOutOfBoundsException) {
		player2->getBoard()->removeCard(minion);
	}
}

void Game::endGame() {
	setExpectingCommand(false);
}

void Game::draw() {
	gameFlags |= 1;
	gameFlags |= 2;
	endGame();
}

void Game::lose(int8_t playerId) {
	gameFlags |= playerId;
	endGame();
}

void Game::processDeaths() {
	int32_t losing = 0;
	if (player1->getHero()->getHealth() <= 0) losing |= 1;
	if (player2->getHero()->getHealth() <= 0) losing |= 2;

	if ((losing & 1) && (losing & 2)) draw();
	else if (losing & 1) lose(1);
	else if (losing & 2) lose(2);

	std::vector<Card*> board1 = player1->getBoard()->getCards();
	std::vector<Card*> board2 = player2->getBoard()->getCards();
	std::vector<Card*> combinedBoard;

	auto lambda = [](Card * a, Card * b) {return a->getOrder() < b->getOrder();};
	std::sort(board1.begin(), board1.end(), lambda);
	std::sort(board2.begin(), board2.end(), lambda);
	size_t i1 = 0, i2 = 0;
	size_t len1 = board1.size(), len2 = board2.size();
	for (size_t i = 0;i < len1 + len2;i++) {
		if ( i1 != len1 && (lambda(board1[i1], board2[i2]) || i2 == len2) ) {
			combinedBoard.push_back(board1[i1++]);
		}
		else {
			combinedBoard.push_back(board2[i2++]);
		}
	}

	for (auto c : combinedBoard) {
		if (c->getHealth() <= 0) minionDeath(c);
	}
}

void Game::dealDamage(Damagable &target, Damagable &source, Player &sourcePlayer, int32_t howMuch) {
	target.takeDamage(howMuch);
}

Card * Game::getCardByIds(int id, int id2, const Player & player)
{
	if (id2 >= 2 && id2 <= 3) {
		Player * opposingPlayer = nullptr;
		if (&player == player1.get()) opposingPlayer = player2.get();
		else if (&player == player2.get()) opposingPlayer = player1.get();
		if (opposingPlayer == nullptr) return nullptr;

		switch (id2) {
		case 2: return opposingPlayer->getBoard()->getCard(id);
		case 3: return opposingPlayer->getHero();
		}
	}
	else {
		switch (id2) {
		case 0: return player.getHero();
		case 1: return player.getBoard()->getCard(id);
		}
	}

	return nullptr;
}


Game::~Game()
{
}
