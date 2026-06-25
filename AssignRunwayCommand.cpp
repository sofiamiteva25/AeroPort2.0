#include "AssignRunwayCommand.h"
#include "FlightCatalog.h"
#include "RunwayCollection.h"
#include "PlaneCollection.h"
#include "RunwayValidator.h"
#include <iostream>
#include "MyException.h"

void AssignRunwayCommand::execute()
{
    const auto& flight = FlightCatalog::getFlightByID(flightId);
    const auto& runway = RunwayCollection::getRunwayById(runwayId);
    const auto& plane = PlaneCollection::getPlaneByID(flight->getPlaneId());

    if (flight->getStatus() != Status::Scheduled)
        throw MyException("FlightIsNotScheduled");
    RunwayValidator::validate(plane.get(), runway.get());
    savedPlaneOnRunway = flight->getPlaneId();
    runway->setPlaneOnRunway(flight->getPlaneId());
}

void AssignRunwayCommand::undo()
{
    const auto& runway = RunwayCollection::getRunwayById(runwayId);
    runway->removePlaneFromRunway();
    runway->setStatus(StatusRunway::RunwayFree);

    std::cout << "UNDO assign-runway: Flight " << flightId;
}

std::unique_ptr<IDispatchCommand> AssignRunwayCommand::clone() const
{
    return std::make_unique<AssignRunwayCommand>(*this);
}
