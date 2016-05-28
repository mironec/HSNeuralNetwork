#include "stdafx.h"
#include "Player.h"


Player::Player(Game * game, std::mt19937_64& randomGen, Deck &deck, HeroType &heroType) {
	hand = std::make_unique<Hand>();
	this->deck = std::make_unique<Deck>(deck);
	board = std::make_unique<Board>();
	hero = std::make_unique<Hero>(&heroType);
	this->randomGen = &randomGen;
	this->game = game;
	mana = maxMana = currentOverload = nextOverload = 0;
	setExpectingCommand(false);
	setExpectedCommandType("");
	inMulligan = false;
	pickedCard = nullptr;
	fatigueDamage = 1;
}

void Player::receiveCommand(const std::shared_ptr<Command> &command) {
	if (command->getType().compare("Cancel") == 0 && inMulligan) { resolveMulligan(pickedCard); pickedCard = nullptr; }
	if (command->getType().compare("EndTurn") == 0 && getExpectedCommandType().compare("Play") == 0) {
		//resolvePlays();
		endTurn();
	}
	else if (getExpectedCommandType().compare("Play") == 0) {
		resolvePlay(command);
	}
	else commands.push_back(std::shared_ptr<Command>(command));
}

std::vector<Card*> Player::getCardChoices() {
	return options;
}

Hand* Player::getHand() const {
	return hand.get();
}

Board * Player::getBoard() const
{
	return board.get();
}

Hero * Player::getHero() const
{
	return hero.get();
}

int8_t Player::getFreeMana()
{
	return mana;
}

int8_t Player::getMaxMana()
{
	return maxMana;
}

/**
 * Tries to decrease mana for the player. If the player does not have
 * enough mana, throws a Player::NotEnoughManaException.
 *
 * @param howMuch how much to decrease the mana by.
 */
void Player::spendMana(int8_t howMuch)
{
	if(howMuch > mana) throw Player::NotEnoughManaException();
	mana -= howMuch;
}

/**
 * Refunds mana to the player after spending it with Player::spendMana(),
 * doesn't perform any checks, so use carefully.
 */
void Player::refundMana(int8_t howMuch)
{
	mana += howMuch;
}

void Player::mulligan(bool isFirst, Card * coinCard) {
	pickedCard = coinCard;
	options.clear();
	for (int i = 0; i < 3 + (isFirst ? 1 : 0);i++) options.push_back(deck->drawRandomCard(*randomGen));

	inMulligan = true;
	setExpectingCommand(true);
	setExpectedCommandType("Select");
}

void Player::resolveMulligan(Card * coinCard)
{
	try {
		int choiceSize = options.size();
		std::vector<bool> selected(choiceSize, false);
		for (size_t i = 0;i < commands.size();i++) {
			if (commands[i]->getType().compare("Select") != 0) throw Command::WrongCommandException(commands[i]);
			if (commands[i]->getArg() < 0 || commands[i]->getArg() >= choiceSize) throw Command::WrongCommandException(commands[i]);

			selected[commands[i]->getArg()] = !selected[commands[i]->getArg()];
		}

		commands.clear();

		for (int i = 0;i < choiceSize;i++) {
			if (!selected[i]) continue;
			Card * replaceCard = deck->drawRandomCard(*randomGen);
			deck->addCardToEnd(options[i]);
			options[i] = replaceCard;
		}

		for (int i = 0;i < choiceSize;i++) {
			hand->addCardToEnd(options[i]);
		}
		if (options.size() == 4) hand->addCardToEnd(coinCard);

		inMulligan = false;

		setExpectingCommand(false);
	}
	catch (const Command::WrongCommandException &e) {
		(void)e;
		commands.clear();
		throw;
	}
}

void Player::endTurn()
{
	setExpectingCommand(false);
}

void Player::startTurn() {
	if (inMulligan) return;

	maxMana++;
	mana = maxMana;

	Card * drawnCard = nullptr;
	try {
		Card * drawnCard = deck->drawRandomCard(*randomGen);
		hand->addCardToEnd(drawnCard);
	}
	catch (const CardContainer::CardContainerFullException &e) { (void)e; }
	catch (const Deck::EmptyDeckException &e) {
		(void)e;
		game->dealDamage(*hero.get(), *hero.get(), *this, fatigueDamage++);
	}

	pickedCard = nullptr;

	setExpectingCommand(true);
	setExpectedCommandType("Play");
}

void Player::resolvePlay(const std::shared_ptr<Command> &command) {
	static int cardPos = 0;
	static CardContainer * cardSource = nullptr;

	if (command->getType().compare("Play") == 0) {
		if (command->getArg() < 0 || command->getArg() >= hand->getNumberOfCards()) throw Command::WrongCommandException(command);
		if (pickedCard != nullptr) throw Command::WrongCommandException(command);
		pickedCard = hand->getCard(command->getArg());
		cardPos = command->getArg();
		cardSource = hand.get();

		if (pickedCard->getTag(CardTag::noTarget)) {
			game->playCard(pickedCard, -1, cardPos);
			pickedCard = nullptr;
			cardSource = nullptr;
		}
	}
	if (command->getType().compare("Pick") == 0) {
		if (command->getArg() < 0 || command->getArg() > board->getNumberOfCards()) throw Command::WrongCommandException(command);
		if (pickedCard != nullptr) throw Command::WrongCommandException(command);
		pickedCard = board->getCard(command->getArg());
		cardPos = command->getArg();
		cardSource = board.get();
	}
	if (command->getType().compare("Target") == 0) {
		if (cardSource == hand.get()) {
			if (command->getArg() < 0 || command->getArg() >= board->getNumberOfCards() + 1) throw Command::WrongCommandException(command);
			if (pickedCard == nullptr) throw Command::WrongCommandException(command);
			game->playCard(pickedCard, command->getArg(), cardPos);
			pickedCard = nullptr;
			cardSource = nullptr;
		}
		else if (cardSource == board.get()) {
			if (command->getArg2() < 0 || command->getArg2() > 3) throw Command::WrongCommandException(command);
			Card * target = game->getCardByIds(command->getArg(), command->getArg2(), *this);
			if (target == nullptr) throw Command::WrongCommandException(command);
			game->minionAttack(pickedCard, target);
		}
	}
}

void Player::resolvePlays() {
	for (size_t i = 0;i < commands.size();i++) {
		Command comm = *commands[i];
		resolvePlay(commands[i]);
	}

	commands.clear();
}

Player::~Player()
{
}

std::string Player::NotEnoughManaException::report() const
{
	return "Not enough mana.";
}

const char * Player::NotEnoughManaException::what() const
{
	return "Not enough mana.";
}
