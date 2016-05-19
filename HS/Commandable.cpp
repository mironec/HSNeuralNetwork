#include "stdafx.h"
#include "Commandable.h"


Commandable::Commandable()
{
}


Commandable::~Commandable()
{
}

bool Commandable::isExpectingCommand()
{
	return expectingCommand;
}

void Commandable::setExpectingCommand(bool value)
{
	expectingCommand = value;
}

std::string Commandable::getExpectedCommandType()
{
	return expectedCommandType;
}

void Commandable::setExpectedCommandType(std::string value)
{
	expectedCommandType = value;
}
