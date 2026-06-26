#include "Airline.h"
#include "AirlineColl.h"
#include "HangarCollection.h"
#include "MyException.h"
Airline::Airline(std::string _name, double _balance)
{
	for (const auto& i : AirlineColl::getAllAirlines()) {
		if (i->getName() == _name|| _balance <= 0) {
			throw MyException("InvalidDataToCreateAirline");
		}
	}
	name = _name;
	balance = _balance;

}

const std::string Airline::getName() const
{
	return name;
}

void Airline::payTax(const int p)
{
	for (const auto& i : HangarCollection::getAllHangars()) {
		for (const auto& j : i->getPlanesInHangar()) {
			if (j == p) {
				if (balance >= i->getTax()) {
					balance -= i->getTax();
					return;
				}
				else {
					throw MyException("YouDoNotHaveEnoughBalanceToPay");

				}
			}
		}
	}
}

void Airline::addPlane(int planeId)
{
	planesId.push_back(planeId);
}

void Airline::addFlight(std::string flightId)
{
	flightsId.push_back(flightId);
}

const double Airline::getBalance() const
{
	return balance;
}

void Airline::addRevenue(double amount)
{
	this->balance += amount;
}

const int Airline::getPlanesSize() const
{
	return planesId.size();
}

const int Airline::getMadeFlights() const
{
	int count = 0;
	for (const auto& i : planesId) {
		if (FlightCatalog::getFlightByPlaneID(i)->getStatus() == Status::Departed) {
			count++;
		}
	}
	return count;
}
