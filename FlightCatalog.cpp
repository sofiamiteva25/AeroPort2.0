#include "FlightCatalog.h"
#include "PlaneCollection.h"
#include "TicketCatalog.h"
#include "MyException.h"
std::vector<std::unique_ptr<Flight>> FlightCatalog::flights;

const std::vector<std::unique_ptr<Flight>>& FlightCatalog::getAllFlights()
{
	return flights;
}

std::vector<std::unique_ptr<Flight>> FlightCatalog::getFlightsByDestination(const std::string& _dest)
{
	std::vector<std::unique_ptr<Flight>> flightsByDestination;
	for (const auto& i : flights) {
		if (i->getDestination() == _dest) {
			flightsByDestination.push_back(i->clone());
		}
	}
	if (flightsByDestination.size() == 0) {
		throw MyException("NoFlightsToDestination");
	}
	return flightsByDestination;
}

std::vector<std::unique_ptr<Flight>> FlightCatalog::getFlightsByPrice(const double& price)
{
	std::vector<std::unique_ptr<Flight>> flightsByPrice;
	for (const auto& i : flights) {
		if (i->getTicketPrice()<=price) {
			flightsByPrice.push_back(i->clone());
		}
	}
	return flightsByPrice;
}

void FlightCatalog::addFlight(std::unique_ptr<Flight>& flight)
{
	for (const auto& i : flights) {
		if (i->getID() == flight->getID())
			throw MyException("CannotAddFlightWithThisId");
	}
	flights.push_back(flight->clone());
}

const std::unique_ptr<Flight>& FlightCatalog::getFlightByID(const std::string& id)
{
	for (const auto& i : flights) {
		if (i->getID() == id)
			return i;
	}
	throw MyException("NoFlightWithThisID");
}

const std::unique_ptr<Flight>& FlightCatalog::getFlightByPlaneID(const int& id)
{
	for (const auto& i : flights) {
		if (i->getPlaneId() == id)
			return i;
	}
	throw MyException("NoFlightWithThisPlaneID");
}

void FlightCatalog::resetFlights()
{
	flights.clear();
}

void FlightCatalog::printAllFlights(std::ostream& os)
{
	for (const auto& i : flights) {
		os << *i;
	}
}


void FlightCatalog::removeFlight(const std::string& flightId)
{
	auto it = std::find_if(flights.begin(), flights.end(), [&flightId](const std::unique_ptr<Flight>& i) {
		return i->getID() == flightId;
		});
	if (it != flights.end()) {
		flights.erase(it);
		return;
	}
	throw MyException("NoFlightWithThisID");
}

double FlightCatalog::getFlightRevenue(const std::string& flightId)
{
	return TicketCatalog::allPaidAmount(flightId) - PlaneCollection::getPlaneByFlightId(flightId)->getTax();
}
