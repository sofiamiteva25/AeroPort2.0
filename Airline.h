#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Hangar.h"
#include "Flightcatalog.h"

class Airline {
	std::string name;
	double balance;
	std::vector<int> planesId;
	std::vector<std::string> flightsId;
public:
	Airline(std::string _name, double _balance);
	const std::string getName() const;
	void payTax(const int p);
	void addPlane(int planeId);
	void addFlight(std::string flightId);
	const double getBalance() const;
	void addRevenue(double amount);
	const int getPlanesSize() const;
	const int getMadeFlights() const;

};
