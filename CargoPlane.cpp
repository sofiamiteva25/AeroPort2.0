#include "CargoPlane.h"
#include "RunwayValidatorVisitor.h"
#include "FlightCatalog.h"
#include "MyException.h"

CargoPlane::CargoPlane(int id, int capacity, const std::string& airlineName): Plane(id, capacity, airlineName)
{
}

void CargoPlane::setTax()
{
    if (AssignedFlight()) {
        this->tax = capacity * 15;
        return;
    }
    throw MyException("ThisPlaneDoesNotHaveFlightAssigned");
}

void CargoPlane::changeHealth()
{
    if (FlightCatalog::getFlightByID(flightID)->getStatus() == Status::Departed) {
        this->health -= 45;
        if (health < 20) {
            this->setCondition(Condition::maintenancePlane);
            return;
        }
        this->setCondition(Condition::freePlane);
    }
}

std::unique_ptr<Plane> CargoPlane::clone() const
{
    return std::make_unique<CargoPlane>(*this);
}

void CargoPlane::printInfo(std::ostream& os) const
{
    Plane::printInfo(os);
    os << "Type: cargoPlane\n";
}

CargoPlane::CargoPlane(const CargoPlane& other): Plane(other.id, other.capacity,
    other.airlineName)
{
    this->con = Condition::freePlane;
    this->health = 100;
}

void CargoPlane::accept(AirportReport& visitor)
{
    visitor.visit(*this);
}

void CargoPlane::reverseHealth()
{
    health += 45;
}

void CargoPlane::acceptValidator(IRunwayValidatorVisitor& v) const
{
    v.visit(*this);
}
