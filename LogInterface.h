#pragma once
#include "Person.h"
class LogInterface
{
	User* user;
public:
	void logout();
	bool isLogged() const;
	void help();
	void printInfo() const;
	void logIn(const std::unique_ptr<User>& p);
	~LogInterface() = default;
	LogInterface();
};
