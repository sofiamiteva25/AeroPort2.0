#include "PrivateJet.h"
#include "RunwayValidatorVisitor.h"
#include "FlightCatalog.h"
#include "MyException.h"
PrivateJet::PrivateJet(int id, int capacity, const std::string& airlineName): Plane(id, capacity, airlineName)
{
}

void PrivateJet::setTax()
{
    if (AssignedFlight()) {
        this->tax = privateJetTax;
        return;
    }
    throw MyException("PlaneHasNoFlightAssigned");
}

void PrivateJet::changeHealth()
{
    if (FlightCatalog::getFlightByID(flightID)->getStatus() == Status::Departed) {
        this->health -= 25;
        if (health < 20) {
            this->setCondition(Condition::maintenancePlane);
            return;
        }
        this->setCondition(Condition::freePlane);
    }
}

std::unique_ptr<Plane> PrivateJet::clone() const
{
    return std::make_unique<PrivateJet>(*this);
}

void PrivateJet::printInfo(std::ostream& os) const
{
    Plane::printInfo(os);
    os << "Type: privateJet \n";
}

PrivateJet::PrivateJet(const PrivateJet& other) : Plane(other.id, other.capacity, other.airlineName)
{
    this->con = Condition::freePlane;
    this->health = 100;
}

void PrivateJet::accept(AirportReport& visitor)
{
    visitor.visit(*this);
}

void PrivateJet::reverseHealth()
{
    health += 25;
}

void PrivateJet::acceptValidator(IRunwayValidatorVisitor& v) const
{
    v.visit(*this);
}
