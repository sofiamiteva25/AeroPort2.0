#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "MyException.h"
class User
{
protected:
	std::string name;
	std::string password;
public:
	const std::string getPassword() const;
	const std::string getName() const;
	friend std::ostream& operator << (std::ostream& os,const std::unique_ptr<User>& p);
	virtual const void help() const = 0;
	virtual ~User() = default;
	User(std::string _name, std::string _password);
	friend std::ostream& operator<<(std::ostream& os, const User& u);
	virtual void print(std::ostream& os) const;
	virtual std::unique_ptr<User> clone() const = 0;
};