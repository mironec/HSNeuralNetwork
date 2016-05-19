#pragma once
#include <string>
#include <memory>
#include "GameplayNotAllowedException.h"

class Command
{
private:
	std::shared_ptr<std::string> type;
	int arg;
	int arg2;
public:
	class WrongCommandException : public GameplayNotAllowedException {
	private:
		std::shared_ptr<Command> command;

	public:
		WrongCommandException(std::shared_ptr<Command> command);
		~WrongCommandException();
		const char * what() const;
		std::string report() const;
	};
	Command(std::string type, int arg = 0, int arg2 = 0);
	~Command();
	std::string getType();
	int getArg();
	int getArg2();
};

