#include "AirlineColl.h"
#include "Airline.h"
#include "MyException.h"
std::vector<std::unique_ptr<Airline>> AirlineColl::airlines;
const std::vector<std::unique_ptr<Airline>>& AirlineColl::getAllAirlines()
{
	return airlines;
}

const std::unique_ptr<Airline>& AirlineColl::getAirlineByName(std::string airlineName)
{
	for (const auto& i : airlines) {
		if (i->getName() == airlineName) {
			return i;
		}
	}
	throw MyException("AirlineNotFound");
}

void AirlineColl::addAirline(std::unique_ptr<Airline> a)
{
	for (const auto& i : AirlineColl::getAllAirlines()) {
		if (i->getName() == a->getName()) {
			throw std::runtime_error("You already added airline with this name");
		}
	}
	airlines.push_back(std::move(a));
}
