#pragma once
#include "Command.h"

class Commandable
{
private:
	bool expectingCommand;
	std::string expectedCommandType;
public:
	Commandable();
	~Commandable();
	virtual void receiveCommand(const std::shared_ptr<Command> &command) = 0;
	bool isExpectingCommand();
	void setExpectingCommand(bool value);
	std::string getExpectedCommandType();
	void setExpectedCommandType(std::string value);
};
