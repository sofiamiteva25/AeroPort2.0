#pragma once
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <iostream>
#include "Flight.h"
class User;
class UserColl;
class MyException;
const int LuggageStandart = 0;
const int LuggageLastMinute = 0;
const int LuggageVIP = 20;

class Ticket
{
protected:
	int id;
	std::string ticketOwner;
	std::string flightID;
	double paidAmount;
	int luggageAmount = 0;
public:
	Ticket(int id,const std::string& owner, const std::string& flightID);
	void setFlightID(std::string flightID);
	void setTicketOwner(const std::string owner);
	void addLuggage(const int& amount);
	const std::string getTicketOwner() const;
	const int& getID() const;
	const std::string getFlightID() const;
	virtual std::unique_ptr<Ticket> clone() const =0;
	const double getPaidAmount() const;
	friend std::ostream& operator<<(std::ostream& os, const Ticket& t);
	virtual void print(std::ostream& os) const;
	int getLuggageAmount() const { return luggageAmount; }
	virtual bool canUpgrade() const = 0;
	virtual bool canRefund() const = 0;
};
