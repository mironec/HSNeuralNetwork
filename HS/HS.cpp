#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "Game.h"
#include "CardStatManager.h"
#include "Card.h"
#include "Deck.h"
#include "GameplayNotAllowedException.h"

using namespace std;

void enumarateCards(vector<Card*> const &c) {
	for (size_t i = 0;i < c.size();i++) {
		if (i != 0) cout << ", ";
		cout << i << ".";
		cout << c[i]->getName();
	}
}

int main()
{
	CardStatManager * cardStatManager = new CardStatManager();

	Deck * deck1 = new Deck();
	Deck * deck2 = new Deck();

	for (int i = 0;i < 30;i++) {
		Card * card = cardStatManager->createDeckCardFromName("Bloodfen Raptor");
		deck1->addCardToEnd(card);

		card = cardStatManager->createDeckCardFromName("River Crocolisk");
		deck2->addCardToEnd(card);
	}

	Game * game = new Game(*deck1, *deck2, HeroType::JAINA, HeroType::JAINA, cardStatManager->createDeckCardFromName("The Coin"));

	cout << "Hello and welcome to the HS simulator." << endl;

	int curPlayer = 0;
	while (game->isExpectingCommand()) {
		if (game->getCurrentPlayerID() != curPlayer) {
			curPlayer = game->getCurrentPlayerID();
			cout << "Player " << curPlayer << " is now playing their turn." << endl;
		}

		if (game->isExpectingCommand()) {
			if (game->getExpectedCommandType().compare("Select") == 0) {
				cout << "Select from options: ";
				vector<Card*> options = game->getCurrentPlayer()->getCardChoices();
				enumarateCards(options); cout << endl;
			}
			if (game->getExpectedCommandType().compare("Play") == 0) {
				cout << "Status: " << "HP" << game->getCurrentPlayer()->getHero()->getHealth() << "/" << game->getCurrentPlayer()->getHero()->getMaxHealth()
					<< " M" << (int)game->getCurrentPlayer()->getFreeMana() << "/" << (int)game->getCurrentPlayer()->getMaxMana() << endl;
				cout << "Your hand: ";
				enumarateCards(game->getCurrentPlayer()->getHand()->getCards()); cout << endl;
				cout << "Your board: ";
				enumarateCards(game->getCurrentPlayer()->getBoard()->getCards()); cout << endl;
			}

			string comm, commType;
			int commArg = 0, commArg2 = 0;
			getline(cin, comm);

			size_t spacePos = comm.find(" ");
			if (spacePos != string::npos) { stringstream ss; commType = comm.substr(0, spacePos); ss << comm.substr(spacePos); ss >> commArg; ss >> commArg2; }
			else commType = comm;

			try {
				game->receiveCommand(make_shared<Command>(commType, commArg, commArg2));
			}
			catch (const GameplayNotAllowedException &e) {
				cout << e.report() << endl;
			}
		}
	}

	system("pause");
	return 0;
}

