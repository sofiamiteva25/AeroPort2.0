#include "User.h"
const std::string User::getPassword() const
{
    return password;
}
const std::string User::getName() const
{
    return name;
}

User::User(std::string _name, std::string _password) : name(_name), password(_password)
{
}
void User::print(std::ostream& os) const
{
    os << name << "\n";
    os << password << "\n";
}

std::ostream& operator<<(std::ostream& os,const std::unique_ptr<User>& p)
{
    p->print(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, const User& u)
{
    u.print(os);
    return os;
}

