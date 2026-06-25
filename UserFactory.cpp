#include "UserFactory.h"
#include "UserColl.h"
#include "Passenger.h"
#include "TraficControl.h"
#include "MyException.h"
UserFactory::UserFactory(std::string name, std::string password, std::string type, double balance)
{
    for (const auto& i : UserColl::getAllUsers()) {
        if (i->getName() == name||type=="Administrator") {
            throw MyException("CannotCreateUser");
        }
    }
    this->name = name;
    this->password = password;
    this->type = type;
    this->balance = balance;
}

std::unique_ptr<User> UserFactory::createUser()
{
    if (type == "Passenger") {
        std::unique_ptr<Passenger> p = std::make_unique<Passenger>(name, password, balance);
        UserColl::addUser(p->clone());
        return p;
    }
    if (type == "TrafficControl") {
        std::unique_ptr<TrafficControl> p = std::make_unique<TrafficControl>(name, password);
        UserColl::addUser(p->clone());
        return p;
    }
    throw MyException("CannotCreateUser");


}
