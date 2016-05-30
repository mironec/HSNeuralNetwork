#include "stdafx.h"
#include "Catch.hpp"
#include "..\HS\Deck.h"
#include "..\HS\Card.h"

TEST_CASE("Deck drawing tests", "[Deck]") {
	Deck * d = new Deck();
	std::mt19937_64 rand = std::mt19937_64();

	SECTION("Deck throws an error when drawing from it when it's empty.") {
		bool thrown = false;
		try {
			d->drawRandomCard(rand);
		}
		catch (const Deck::EmptyDeckException &e) {
			(void)e;
			thrown = true;
		}

		REQUIRE(thrown);
	}

	SECTION("Deck with one card can be drawn from and returns the only card.") {
		Card * c = new Card();
		d->addCardToEnd(c);
		Card * c2 = d->drawRandomCard(rand);

		REQUIRE(c == c2);

		SECTION("Deck with one card after the card is drawn is empty and cannot be drawn from.") {
			bool thrown = false;
			try {
				d->drawRandomCard(rand);
			}
			catch (const Deck::EmptyDeckException &e) {
				(void)e;
				thrown = true;
			}

			REQUIRE(thrown);
		}
	}

	SECTION("Deck with 5 cards can be drawn exactly 5 times.") {
		Card * c = new Card();
		for (int i = 0;i < 5;i++) d->addCardToEnd(c);

		for (int i = 0;i < 5;i++) d->drawRandomCard(rand);

		bool thrown = false;
		try {
			d->drawRandomCard(rand);
		}
		catch (const Deck::EmptyDeckException &e) {
			(void)e;
			thrown = true;
		}

		REQUIRE(thrown);
	}

	SECTION("Deck with one card added and removed repeatedly behaves normally.") {
		for (int i = 0;i < 5;i++) {
			Card * c = new Card();
			d->addCardToEnd(c);
			REQUIRE(c == d->drawRandomCard(rand));
			
			bool thrown = false;
			try {
				d->drawRandomCard(rand);
			}
			catch (const Deck::EmptyDeckException &e) {
				(void)e;
				thrown = true;
			}

			REQUIRE(thrown);
		}
	}
}
