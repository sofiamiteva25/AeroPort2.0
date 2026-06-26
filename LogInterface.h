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
	void logIn(std::string name, std::string password);
	~LogInterface() = default;
	LogInterface();
	User* getUser() const;
	void signUp(std::string name, std::string password, std::string type, double balance=0);

};
