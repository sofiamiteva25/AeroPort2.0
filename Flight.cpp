#include "Flight.h"
#include "PlaneCollection.h"
#include "AirlineColl.h"
#include "Airline.h"
#include "FlightCatalog.h"
#include "MyException.h"

Flight::Flight(const std::string& id, int planeId, const double& ticketAmount, const std::string& destination)
{
	for (const auto& i : FlightCatalog::getAllFlights()) {
		if (i->getID() == id) {
			throw MyException("CannotAddFlightWithThisId");
		}
	}
	this->id = id;
	this->planeId = planeId;
	this->ticketAmount = ticketAmount;
	this->destination = destination;
	this->status = Status::Scheduled;
	PlaneCollection::getPlaneByID(planeId)->assignFlight(this->id);
	AirlineColl::getAirlineByName(PlaneCollection::getPlaneByID(planeId)->getAirline())->addFlight(id);
}

const std::string Flight::getDestination() const
{
	return destination;
}

const double Flight::getTicketPrice() const
{
	return ticketAmount;
}

const std::vector<int>& Flight::getTickets() const
{
	return ticketsId;
}

const Status Flight::getStatus() const
{
	return status;
}

const std::string Flight::getID() const
{
	return id;
}

bool Flight::canBook() const
{
	if (ticketsId.size() < PlaneCollection::getPlaneByID(planeId)->getCap())
		return true;
	return false;
}

void Flight::addTicket(int ticketId)
{
	if (canBook()) {
		for (const auto& i : ticketsId) {
			if (i == ticketId) {
				throw MyException("AlreadyAdded");
			}
		}
		ticketsId.push_back(ticketId);
		return;
	}
	throw MyException("FlightFull");
}

const int Flight::getPlaneId() const
{
	return planeId;
}

std::unique_ptr<Flight> Flight::clone() const
{
	return std::make_unique<Flight>(*this);
}


void Flight::setStatus(const Status& newStatus)
{
	if (status != newStatus) {
		status = newStatus;
	}
}

const double Flight::getTicketAmount() const
{
	return ticketAmount;
}

std::ostream& operator<<(std::ostream& os, const Flight& flight)
{
	os << "ID: " << flight.id << "\n";
	os << "PplaneId: " << flight.planeId << "\n";
	os << "TicketPrice: " << flight.ticketAmount << "\n";
	os << "Destination: " << flight.destination << "\n";
	os << "Status: " << flight.status << "\n";
	return os;
}
