#include "DelayFlightCommand.h"
#include "FlightCatalog.h"
#include "TicketCatalog.h"
#include <iostream>
#include "MyException.h"

void DelayFlightCommand::execute()
{
    const auto& flight = FlightCatalog::getFlightByID(flightId);
    previousStatus = flight->getStatus();

    if (previousStatus == Status::Departed || previousStatus == Status::Cancelled)
        throw MyException("CannotDelayFlight");

    flight->setStatus(Status::Delayed);

    std::cout << "Flight delayed" << reason << "\n";

    try {
        auto tickets = TicketCatalog::getTicketsByFlightId(flightId);
        for (const auto& t : tickets) {
            std::cout << "      [MSG → " << t->getTicketOwner()
                << "] Your flight " << flightId
                << " is delayed. Reason: " << reason << "\n";
        }
    }
    catch (...) {
    }
}

void DelayFlightCommand::undo()
{
    const auto& flight = FlightCatalog::getFlightByID(flightId);
    flight->setStatus(previousStatus);
}

std::unique_ptr<IDispatchCommand> DelayFlightCommand::clone() const
{
    return std::make_unique<DelayFlightCommand>(*this);
}