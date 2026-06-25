#include "FreeRunwayCommand.h"
#include "RunwayCollection.h"
#include "PlaneCollection.h"
#include "FlightCatalog.h"
#include "AirlineColl.h"
#include "Airline.h"
#include "TicketCatalog.h"
#include <iostream>
#include "MyException.h"
void FreeRunwayCommand::execute()
{
    const auto& runway = RunwayCollection::getRunwayById(runwayId);

    if (runway->getStatus() != StatusRunway::RunwayOccupied)
        throw MyException("RunwayFree");

    savedPlaneId = runway->getPlaneOnRunway();
    const auto& plane = PlaneCollection::getPlaneByID(savedPlaneId);
    savedFlightId = plane->getFlight();

    const auto& flight = FlightCatalog::getFlightByID(savedFlightId);
    const auto& airline = AirlineColl::getAirlineByName(plane->getAirline());
    flight->setStatus(Status::Departed);
    plane->setTax();
    double totalTickets = TicketCatalog::allPaidAmount(savedFlightId);
    double airportTax = plane->getTax();
    double airlineRev = totalTickets - airportTax;
    plane->changeHealth();
    airline->addRevenue(airlineRev);
    runway->setStatus(StatusRunway::RunwayFree);
}

void FreeRunwayCommand::undo()
{
    const auto& flight = FlightCatalog::getFlightByID(savedFlightId);
    const auto& runway = RunwayCollection::getRunwayById(runwayId);
    const auto& plane = PlaneCollection::getPlaneByID(savedPlaneId);
    const auto& airline = AirlineColl::getAirlineByName(plane->getAirline());
    double totalTickets = TicketCatalog::allPaidAmount(savedFlightId);
    double airportTax = plane->getTax();
    double airlineRev = totalTickets - airportTax;
    airline->addRevenue(-airlineRev); 
    plane->reverseHealth();
    flight->setStatus(Status::Boarding);
    runway->setStatus(StatusRunway::RunwayOccupied);

    std::cout << " UNDO free-runway: Flight " << savedFlightId;
}

std::unique_ptr<IDispatchCommand> FreeRunwayCommand::clone() const
{
    return std::make_unique<FreeRunwayCommand>(*this);
}
