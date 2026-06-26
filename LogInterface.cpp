#include "LogInterface.h"
#include "MyException.h"
void LogInterface::logout()
{
    if (isLogged()) {
        user = nullptr;
    }
}

bool LogInterface::isLogged() const
{
    if (user != nullptr) {
        return true;
    }
    return false;
}

void LogInterface::help()
{
    user->help();
}

void LogInterface::printInfo() const
{
    std::cout << *user;
}

void LogInterface::logIn(std::string name, std::string password)
{
    try {
        if (name == "admin" && password == "admin") {
            user = Administrator::getInstance();
            return;
        }
        if (UserColl::getUserByName(name)) {
            if (UserColl::getUserByName(name)->getPassword() == password) {
                user = UserColl::getUserByName(name).get();
            }
        }
        else
            throw MyException("RegisterFirst");
    }
    catch (MyException& e) {
        std::cout << e.what() << '\n';
    }
}

LogInterface::LogInterface()
{
    user = nullptr;
}

User* LogInterface::getUser() const {
    return user;
}

void LogInterface::signUp(std::string name, std::string password, std::string type, double balance)
{
    try {
        if (!UserColl::isUser(name)) {
            UserFactory f(name, password, type, balance);
            f.createUser();
            user = UserColl::getUserByName(name).get();
        }
    }
    catch (MyException& e) {
        e.what();
    }
}
