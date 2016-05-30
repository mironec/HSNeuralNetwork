#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "Catch.hpp"
#include "..\HS\CardType.h"

TEST_CASE("CardTag tests", "[CardTag]") {
	SECTION("CardTag vacuously true.") {
		REQUIRE(CardTag::minion == CardTag::minion);
		REQUIRE(CardTag::beast == CardTag::beast);
		REQUIRE(CardTag::spell == CardTag::spell);
		REQUIRE(CardTag::hero == CardTag::hero);
		REQUIRE(CardTag::noTarget == CardTag::noTarget);
	}

	SECTION("CardType with all CardTags returns true for all tag queries.") {
		CardType * dummy = new CardType();
		dummy->setTags(CardTag::minion | CardTag::beast | CardTag::hero | CardTag::noTarget | CardTag::spell);

		REQUIRE(dummy->getTag(CardTag::minion));
		REQUIRE(dummy->getTag(CardTag::beast));
		REQUIRE(dummy->getTag(CardTag::hero));
		REQUIRE(dummy->getTag(CardTag::spell));
		REQUIRE(dummy->getTag(CardTag::noTarget));
	}

	SECTION("CardType with no CardTags returns false for all tag queries.") {
		CardType * dummy = new CardType();
		dummy->setTags(static_cast<CardTag>(0));

		REQUIRE(!dummy->getTag(CardTag::minion));
		REQUIRE(!dummy->getTag(CardTag::beast));
		REQUIRE(!dummy->getTag(CardTag::hero));
		REQUIRE(!dummy->getTag(CardTag::spell));
		REQUIRE(!dummy->getTag(CardTag::noTarget));
	}

	SECTION("CardType with some CardTags returns false for all other tag queries.") {
		CardType * dummy = new CardType();
		dummy->setTags(CardTag::minion | CardTag::beast);

		REQUIRE(dummy->getTag(CardTag::minion));
		REQUIRE(dummy->getTag(CardTag::beast));
		REQUIRE(!dummy->getTag(CardTag::hero));
		REQUIRE(!dummy->getTag(CardTag::spell));
		REQUIRE(!dummy->getTag(CardTag::noTarget));
	}
}
