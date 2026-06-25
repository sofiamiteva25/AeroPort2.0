#pragma once
#include <string>
#include "User.h"

class UserFactory {
	std::string name;
	std::string password;
	std::string type;
	double balance = 0;
public:
	UserFactory(std::string name,
		std::string password,
		std::string type, double balance=0);
	std::unique_ptr<User> createUser();

};
