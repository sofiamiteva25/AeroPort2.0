#include "UserColl.h"
#include "MyException.h"
std::vector<std::unique_ptr<User>> UserColl::users;

const std::vector<std::unique_ptr<User>>& UserColl::getAllUsers()
{
    return users;
}

const std::unique_ptr<User>& UserColl::getUserByName(std::string name)
{
    for (const auto& i : UserColl::getAllUsers()) {
        if (i->getName() == name) {
            return i;
        }
    }
    throw MyException("PassengerWithThisNameNotFound");
}

void UserColl::addUser(std::unique_ptr<User> u)
{
    users.push_back(std::move(u));
}
