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

void LogInterface::logIn(const std::unique_ptr<User>& p)
{
    auto it = std::find_if(UserColl::getAllUsers().begin(), UserColl::getAllUsers().end(), [&p](const std::unique_ptr<User>& i) {
        if (i->getName() == p->getName())
            return i->getPassword() == p->getPassword();
        else {
            return false;
        }});
        if (it != UserColl::getAllUsers().end()) {
            if (!isLogged()) {
                user = p.get();
            }
        }
        else
            throw MyException("RegisterFirst");
}

LogInterface::LogInterface()
{
    user = nullptr;
}
