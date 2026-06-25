#include "Runway.h"
#include "PlaneCollection.h"
#include "FlightCatalog.h"
#include "MyException.h"
int Runway::count = 1;

Runway::Runway(const unsigned int& length, bool ils, bool heavyDuty, bool vipTerminal)
	: length(length), ils(ils), heavyDuty(heavyDuty), vipTerminal(vipTerminal), planeOnRunway(0)
{
	idRunway = count++;
	status = StatusRunway::RunwayFree;
}

unsigned int Runway::getLength() const
{
	return length;
}

bool Runway::hasHeavyDuty() const
{
	return heavyDuty;
}

bool Runway::hasVIP() const
{
	return vipTerminal;
}

bool Runway::hasILS() const
{
	return ils;
}

std::unique_ptr<Runway> Runway::clone() const
{
	return std::unique_ptr<Runway>(new Runway(length, ils, heavyDuty, vipTerminal));
}

const int& Runway::getPlaneOnRunway() const
{
	return planeOnRunway;
}

const int Runway::getID() const
{
	return idRunway;
}

StatusRunway Runway::getStatus() const
{
	return status;
}

void Runway::setPlaneOnRunway(const int& planeId)
{
	if (planeOnRunway != 0) {
		std::cout << "CannotAddPlane";
		return;
	}
	std::string flight = PlaneCollection::getPlaneByID(planeId)->getFlight();
	if (FlightCatalog::getFlightByID(flight)->getStatus() == Status::Scheduled) {
		planeOnRunway = planeId;
		this->setStatus(StatusRunway::RunwayOccupied);
		FlightCatalog::getFlightByID(flight)->setStatus(Status::Boarding);
		return;
	}
	else {
		throw MyException("PlaneNotScheduled");
	}
}

void Runway::setStatus(const StatusRunway& newStatus)
{
	if(this->getStatus()!=newStatus)
		status = newStatus;
}

void Runway::removePlaneFromRunway()
{
	std::string flight = PlaneCollection::getPlaneByID(planeOnRunway)->getFlight();
	if (FlightCatalog::getFlightByID(flight)->getStatus() == Status::Boarding) {
		planeOnRunway = 0;
		FlightCatalog::getFlightByID(flight)->setStatus(Status::Scheduled);
		return;
	}
}

std::ostream& operator<<(std::ostream& os, const Runway& runway)
{
	os << "Id: " << runway.idRunway << "\n";
	os << "Length: " << runway.length << "\n";
	os << "Status: " << runway.status << "\n";
	os << "ILS: " << (runway.ils ? "Yes" : "No") << "\n";
	os << "HeavyDuty: " << (runway.heavyDuty ? "Yes" : "No") << "\n";
	os << "VIPTerminal: " << (runway.vipTerminal ? "Yes" : "No") << "\n";
	return os;
}


Runway::Builder& Runway::Builder::withLength(const unsigned int& len)
{
	length = len;
	return *this;
}

Runway::Builder& Runway::Builder::withILS()
{
	ils = true;
	return *this;
}

Runway::Builder& Runway::Builder::withHeavyDuty()
{
	heavyDuty = true;
	return *this;
}

Runway::Builder& Runway::Builder::withVIPTerminal()
{
	vipTerminal = true;
	return *this;
}

std::unique_ptr<Runway> Runway::Builder::build() const
{
	if (length == 0) {
		throw MyException("RunwayLengthMustBeSet");
	}
	return std::unique_ptr<Runway>(new Runway(length, ils, heavyDuty, vipTerminal));
}
