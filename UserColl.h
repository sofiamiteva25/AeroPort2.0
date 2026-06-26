#pragma once
#include <vector>
#include <memory>
#include <string>
#include "User.h"

class UserColl {
	static std::vector<std::unique_ptr<User>> users;
public:
	static const std::vector<std::unique_ptr<User>>& getAllUsers();
	static const std::unique_ptr<User>& getUserByName(std::string name);
	static void addUser(std::unique_ptr<User> u);
	static bool isUser(std::string name);
};
