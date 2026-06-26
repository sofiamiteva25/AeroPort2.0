#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "WeatherDesign.h"
#include "Ticket.h"
#include <string>
#include "Hangar.h"
#include "Runway.h"
#include "User.h"
#include "Flight.h"

class Passenger : public User
{
protected:
	double balance;
public:
	Passenger(std::string _name, std::string _password, double _balance = 0.0)
		: User(_name, _password), balance(_balance) {
		WeatherDesign::getInstance()->addObserver(this->name);
	}
	double& addFunds(const double& amount);
	std::vector<std::unique_ptr<Flight>> listFlightByDestination(const std::string& _destination);
	std::vector<std::unique_ptr<Flight>> filterFlightsByPrice(const double& maxPrice);
	std::vector<std::unique_ptr<Ticket>> myTickets();
	void bookTicket(const std::string flightId, const std::string type);
	void upgradeTicket(const std::string flightId, std::string newType);
	void cancelTicket(const std::string& flightId);
	void addLuggage(const std::string& flightId, const int& luggageAmount);
	const double getBalance() const;
	void refundTicket(const std::string& flightId);
	const void help() const override;
	void print(std::ostream& os) const override;
	std::unique_ptr<User> clone() const override;

};
