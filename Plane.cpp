#include "Plane.h"
#include "RunwayValidatorVisitor.h"
#include "AirlineColl.h"
#include "Airline.h"
#include "FlightCatalog.h"
#include "MyException.h"
Plane::Plane(int id, int capacity, const std::string& airlineName): id(id), capacity(capacity)
{
    setAirline(airlineName);
    this->health = 100;
    this->con = Condition::freePlane;
    this->tax = 0;
}

const int Plane::getCap() const
{
    return capacity;
}

const int Plane::getID() const
{
    return id;
}

const std::string& Plane::getAirline() const
{
    return airlineName;
}

const bool Plane::inHangar() const
{
    return con == Condition::inHangar;
}


void Plane::setCondition(Condition c)
{
    con = c;
}

bool Plane::AssignedFlight() const
{
    if (flightID=="") {
        return false;
    }
    return true;
}

void Plane::printInfo(std::ostream& os) const
{
    os << "Id: " << id << "\n";
    os << "Health: " << health << "\n";
    os << "Capacity: " << capacity << "\n";
    os << "Condition: " << con << "\n";
    os << "Airline: " << airlineName << "\n";

}

const Condition Plane::getCon() const
{
    return con;
}

void Plane::resetHealth()
{
    this->health = 100;
}

const double Plane::getTax() const
{
    return tax;
}

void Plane::setAirline(std::string airlineName)
{
    for (const auto& i : AirlineColl::getAllAirlines()) {
        if (i->getName() == airlineName) {
            this->airlineName = airlineName;
            return;
        }
    }
    throw MyException("AirlineNotFound");
}

void Plane::assignFlight(std::string flightID)
{
    if (con == Condition::freePlane) {
        for (const auto& i : FlightCatalog::getAllFlights()) {
            if (i->getID() == flightID) {
                this->flightID = flightID;
                con = Condition::occupiedPlane;
            }
        }
    }
}

const std::string Plane::getFlight() const
{
    return flightID;
}

void Plane::freePlane()
{
    flightID = "";
    this->setCondition(Condition::freePlane);
}

std::ostream& operator<<(std::ostream& os, const Plane& plane)
{
    plane.printInfo(os);
    return os;
}
