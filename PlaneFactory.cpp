#include "PlaneFactory.h"
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include "PlaneCollection.h"
#include "AirlineColl.h"
#include "Airline.h"
#include "MyException.h"
int PlaneFactory::count = 1;

PlaneFactory::PlaneFactory(std::string _type, int _capacity): type(_type), capacity(_capacity)
{
}

void PlaneFactory::createPlane(const std::string& airlineName)
{
    if (type == "PassengerPlane") {
        std::unique_ptr<PassengerPlane> pPtr = std::make_unique<PassengerPlane>(count, capacity, airlineName);
        AirlineColl::getAirlineByName(airlineName)->addPlane(count);
        count++;
        PlaneCollection::addPlane(std::move(pPtr));
    }
    else if (type == "CargoPlane") {
        std::unique_ptr<CargoPlane> pPtr = std::make_unique<CargoPlane>(count, capacity, airlineName);
        AirlineColl::getAirlineByName(airlineName)->addPlane(count);
        count++;
        PlaneCollection::addPlane(std::move(pPtr));
    }
    else if (type == "PrivateJet") {
        std::unique_ptr<PrivateJet> pPtr = std::make_unique<PrivateJet>(count, capacity, airlineName);
        AirlineColl::getAirlineByName(airlineName)->addPlane(count);
        count++;
        PlaneCollection::addPlane(std::move(pPtr));

    }
    else { throw MyException("NotPossibleType"); }
}

void PlaneFactory::resetCount()
{
    count = 0;
}
