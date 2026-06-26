#include "TraficControl.h"
#include "AssignRunwayCommand.h"
#include "FreeRunwayCommand.h"
#include "DelayFlightCommand.h"
#include "FlightCatalog.h"
#include "PlaneCollection.h"
#include "RunwayCollection.h"

void TrafficControl::executeAndRecord(std::unique_ptr<IDispatchCommand> cmd)
{
    cmd->execute();
    history.push_back(std::move(cmd));
}

TrafficControl::TrafficControl(const TrafficControl& other): User(other.name, other.password)
{

    for (const auto& i : other.history) {
        history.push_back(i->clone());
    }
}

void TrafficControl::listAirspace() const
{
    for (const auto& i:FlightCatalog::getAllFlights()) {
        if (i->getStatus() == Status::Scheduled) {
            std::cout << *PlaneCollection::getPlaneByFlightId(i->getID());
        }
    }
}

void TrafficControl::listRunways() const
{
    for (const auto& r : RunwayCollection::getAllRunways()) {
        std::cout << r->getID() << "\n";
        std::cout << r->getLength() << "\n";
        std::cout << r->getStatus() << "\n";
        if (r->getStatus() == StatusRunway::RunwayOccupied) {
            std::cout << r->getPlaneOnRunway() << "\n";
        }

    }
}

void TrafficControl::assignRunway(const std::string& flightId, int runwayId)
{
    try {
        executeAndRecord(std::make_unique<AssignRunwayCommand>(flightId, runwayId));
    }
    catch (MyException& e) {
        e.what();
    }

}

void TrafficControl::delayFlight(const std::string& flightId, const std::string& reason)
{
    try {
        executeAndRecord(std::make_unique<DelayFlightCommand>(flightId, reason));
    }
    catch (MyException& e) {
        e.what();
    }
}

void TrafficControl::freeRunway(int runwayId)
{
    try {
        executeAndRecord(std::make_unique<FreeRunwayCommand>(runwayId));
    }
    catch (MyException& e) {
        e.what();
    }
}

void TrafficControl::undo()
{
    if (history.empty()) {
        std::cout << "Nothing to undo.\n";
        return;
    }
    try {
        history.back()->undo();
        history.pop_back();
    }
    catch (const MyException& e) {
        e.what();
    }
}

const void TrafficControl::help() const
{
    std::cout << "1.ListAirspace\n";
    std::cout << "2.ListRunways\n";
    std::cout << "3.AssignRunway\n";
    std::cout << "4.DelayFlight\n";
    std::cout << "5.FreeRunway\n";
    std::cout << "6.Undo\n";
    std::cout << "7.Logout\n";
    std::cout << "8.Save\n";
    std::cout << "9.Load\n";
    std::cout << "10.Exit\n";
}

void TrafficControl::print(std::ostream& os) const
{
    os << "Name: " << name << "\n";
    os << "Password: " << password << "\n";
    os << "Type: TrafficControl" << "\n";

}

std::unique_ptr<User> TrafficControl::clone() const
{
    return std::make_unique<TrafficControl>(*this);
}
