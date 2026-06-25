#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <optional>
#include "Ticket.h"
#include <iostream>
#include "Flight.h"
#include "AirportReport.h"
#include "AirlineColl.h"
class MyException;
class IRunwayValidatorVisitor;
const int privateJetTax = 5000;
enum Condition {
	freePlane,
	occupiedPlane,
	maintenancePlane,
	inHangar
};

class Plane
{
protected:
	int id;
	int health;
	double tax;
	int capacity;
	Condition con;
	std::string airlineName;
	std::string flightID;
public:
	Plane() = default;
	Plane(int id, int capacity,
		const std::string& airlineName);
	virtual void setTax() = 0;
	const int getCap() const;
	const int getID() const;
	virtual void changeHealth() = 0;
	virtual~Plane() = default;
	const std::string& getAirline() const;
	const bool inHangar() const;
	void setCondition(Condition c);
	bool AssignedFlight() const;
	virtual std::unique_ptr<Plane> clone() const = 0;
	virtual void printInfo(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const Plane& plane);
	const Condition getCon() const;
	void resetHealth();
	virtual void accept(AirportReport& visitor) = 0;
	const double getTax() const;
	void setAirline(std::string airlineName);
	void assignFlight(std::string flightID);
	const std::string getFlight() const;
	void freePlane();
	virtual void reverseHealth() = 0;
	virtual void acceptValidator(IRunwayValidatorVisitor& v) const = 0;
};
