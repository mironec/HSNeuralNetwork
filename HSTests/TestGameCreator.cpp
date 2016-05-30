#include "stdafx.h"
#include "TestGameCreator.h"

std::unique_ptr<Game> TestGameCreator::getCrocoliskGame()
{
	std::unique_ptr<Deck> d1 = std::make_unique<Deck>();
	std::unique_ptr<Deck> d2 = std::make_unique<Deck>();
	std::unique_ptr<CardStatManager> csm = std::make_unique<CardStatManager>();

	for (int i = 0;i < 30;i++) {
		Card * card = csm->createDeckCardFromName("River Crocolisk");
		d1->addCardToEnd(card);

		card = csm->createDeckCardFromName("River Crocolisk");
		d2->addCardToEnd(card);
	}

	return std::make_unique<Game>(*d1.get(),*d2.get(), HeroType::JAINA, HeroType::JAINA, csm->createDeckCardFromName("The Coin"));
}
