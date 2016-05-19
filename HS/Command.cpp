#include "stdafx.h"
#include "Command.h"


Command::Command(std::string type, int arg, int arg2): arg(arg), arg2(arg2)
{
	this->type = std::make_shared<std::string>(type);
}


Command::~Command()
{
}

std::string Command::getType()
{
	return *(type.get());
}

int Command::getArg()
{
	return arg;
}

int Command::getArg2()
{
	return arg2;
}

Command::WrongCommandException::WrongCommandException(std::shared_ptr<Command> c) {
	this->command = c;
}

Command::WrongCommandException::~WrongCommandException()
{
}

const char * Command::WrongCommandException::what() const
{
	return "Invalid command.";
}

std::string Command::WrongCommandException::report() const
{
	return "Invalid command: "+command->getType();
}
