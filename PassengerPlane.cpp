#include "PassengerPlane.h"
#include "RunwayValidatorVisitor.h"
#include "FlightCatalog.h"
#include "TicketCatalog.h"
#include "MyException.h"
PassengerPlane::PassengerPlane(int id, int capacity, const std::string& airlineName): Plane(id, capacity, airlineName)
{
}

void PassengerPlane::setTax()
{
    if (AssignedFlight()) {
        this->tax = TicketCatalog::allPaidAmount(flightID) * 0.1;
        return;
    }
    throw MyException("PlaneHasNoFlightAssigned");
    
}

void PassengerPlane::changeHealth()
{
    if (FlightCatalog::getFlightByID(flightID)->getStatus() == Status::Departed) {
        this->health -= 35;
        if (health < 20) {
            this->setCondition(Condition::maintenancePlane);
            return;
        }
        this->setCondition(Condition::freePlane);
    }
}

std::unique_ptr<Plane> PassengerPlane::clone() const
{
    return std::make_unique<PassengerPlane>(*this);
}

void PassengerPlane::printInfo(std::ostream& os) const
{
    Plane::printInfo(os);
    os << "Type: passengerPlane \n";
}

PassengerPlane::PassengerPlane(const PassengerPlane& other): Plane(other.id, other.capacity, other.airlineName)
{
    this->con = Condition::freePlane;
    this->health = 100;
}

void PassengerPlane::accept(AirportReport& visitor)
{
    visitor.visit(*this);
}

void PassengerPlane::reverseHealth()
{
    health += 35;
}

void PassengerPlane::acceptValidator(IRunwayValidatorVisitor& v) const
{
    v.visit(*this);
}
