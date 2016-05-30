#include "stdafx.h"
#include "Catch.hpp"
#include "..\HS\Game.h"
#include "..\HS\Command.h"
#include "..\HS\GameplayNotAllowedException.h"
#include "TestGameCreator.h"
#include <memory>

TEST_CASE("Minions cannot attack minions or heroes on the same side of the board.", "[Game]") {
	std::unique_ptr<Game> g = TestGameCreator::getCrocoliskGame();
	g->receiveCommand(std::make_shared<Command>("Cancel", 0, 0));
	g->receiveCommand(std::make_shared<Command>("Cancel", 0, 0));
	g->receiveCommand(std::make_shared<Command>("EndTurn", 0, 0));
	g->receiveCommand(std::make_shared<Command>("EndTurn", 0, 0));
	g->receiveCommand(std::make_shared<Command>("Play", 0, 0));
	g->receiveCommand(std::make_shared<Command>("EndTurn", 0, 0));
	g->receiveCommand(std::make_shared<Command>("EndTurn", 0, 0));
	g->receiveCommand(std::make_shared<Command>("Pick", 0, 1));

	bool thrown = false;
	try {
		g->receiveCommand(std::make_shared<Command>("Target", 0, 1));
	}
	catch (const GameplayNotAllowedException &e) {
		(void)e;
		thrown = true;
	}

	REQUIRE(thrown);
}
