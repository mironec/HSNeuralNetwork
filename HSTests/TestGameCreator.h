#pragma once
#include "..\HS\Game.h"
#include "..\HS\Deck.h"
#include "..\HS\CardStatManager.h"
#include <memory>

namespace TestGameCreator
{
	std::unique_ptr<Game> getCrocoliskGame();
};

