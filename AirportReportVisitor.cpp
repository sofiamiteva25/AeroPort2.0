#include "AirportReportVisitor.h"
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include "FlightCatalog.h"

void AirportReportVisitor::visit(PassengerPlane& p)
{
    if (FlightCatalog::getFlightByPlaneID(p.getID())->getStatus() == Status::Departed) {
        passengerTax += p.getTax();
        passengerCount++;
    }
}

void AirportReportVisitor::visit(CargoPlane& p)
{
    if (FlightCatalog::getFlightByPlaneID(p.getID())->getStatus() == Status::Departed) {
        cargoTax += p.getTax();
        cargoCount++;
    }
}

void AirportReportVisitor::visit(PrivateJet& p)
{
    if (FlightCatalog::getFlightByPlaneID(p.getID())->getStatus() == Status::Departed) {
        privateTax += p.getTax();
        privateCount++;
    }
}

void AirportReportVisitor::printReport(std::ostream& os) const
{
    os << "Passenger Planes: " << passengerCount <<  "\n";
    os << "Tax collected: " << passengerTax << "\n";
    os << "Cargo Planes:  " << cargoCount << "\n";
    os << "Tax collected: " << cargoTax << "\n";
    os << "Private Jets:  " << privateCount << "\n";
    os << "Tax collected: " << privateTax << "\n";
    os << "Total airport revenue: " << "\n";
    os << getTotal() << "\n";
}

double AirportReportVisitor::getTotal() const
{
    return passengerTax + cargoTax + privateTax;
}
