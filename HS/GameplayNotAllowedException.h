#pragma once
#include <exception>
#include <string>

class GameplayNotAllowedException : public std::exception
{
public:
	GameplayNotAllowedException();
	~GameplayNotAllowedException();
	virtual std::string report() const = 0;
};

