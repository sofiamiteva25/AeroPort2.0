#include "Administrator.h"
#include "Passenger.h"
#include "UserColl.h"
#include "FlightCatalog.h"
#include "PlaneCollection.h"
#include "PlaneFactory.h"
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include "RunwayCollection.h"
#include "HangarCollection.h"
#include "AirlineColl.h"
#include "Airline.h"
#include "AirportReportVisitor.h"
#include "TicketCatalog.h"
#include "MyException.h"

Administrator* Administrator::instance = new Administrator("admin", "admin");

void Administrator::cancelFlight(const std::string& flightId)
{
    std::vector<std::string> owners;
    for (const auto& j : TicketCatalog::getTicketsByFlightId(flightId))
        owners.push_back(j->getTicketOwner());

    for (const std::string& name : owners) {
        Passenger* p = dynamic_cast<Passenger*>(
            UserColl::getUserByName(name).get()
            );
        if (p) p->refundTicket(flightId);
    }

    FlightCatalog::getFlightByID(flightId)->setStatus(Status::Cancelled);
    PlaneCollection::getPlaneByFlightId(flightId)->freePlane();
}

Administrator::Administrator(const std::string& name, const std::string& password)
    :User(name, password)
{
}

Administrator* Administrator::getInstance()
{
    return instance;
}

void Administrator::buildRunway(const unsigned int length, bool ils, bool heavy, bool vip)
{
    Runway::Builder builder;
    builder.withLength(length);

    if (ils) {
        builder.withILS();
    }
    if (heavy) {
        builder.withHeavyDuty();
    }
    if (vip) {
        builder.withVIPTerminal();
    }

    std::unique_ptr<Runway> runway = builder.build();
    RunwayCollection::addRunway(runway);
}

void Administrator::buildHangar(const std::string id, const int capacity, const double tax)
{
    Hangar newH(capacity, tax, id);
    HangarCollection::addHangar(std::make_unique<Hangar>(newH));
    
}

void Administrator::closeRunway(const int& runwayId)
{
    RunwayCollection::getRunwayById(runwayId)->setStatus(StatusRunway::RunwayMaintenance);
    RunwayCollection::getRunwayById(runwayId)->removePlaneFromRunway();

}

void Administrator::changeWeather(const WeatherCondition& weather)
{
    WeatherDesign::getInstance()->updateWeather(weather);
}

void Administrator::cloneAircraft(const int aircraftId, int count)
{
    std::string type;
    int         cap;
    std::string airline;

    {
        const std::unique_ptr<Plane>& original = PlaneCollection::getPlaneByID(aircraftId);
        type = Administrator::getPlaneType(original.get());
        cap = original->getCap();
        airline = original->getAirline();
    }

    PlaneFactory factory(type, cap);
    for (int i = 0; i < count; i++) {
        factory.createPlane(airline);
    }
}

void Administrator::sentPlaneToHangar(const int& planeId, const std::string& hangarId)
{
    for (const auto& i : HangarCollection::getAllHangars()) {
        if (i->getId() == hangarId) {
            i->addPlane(planeId);
            i->payTax(planeId);
        }
    }
}

void Administrator::scheduleFlight(const std::string& flightId, const int& planeId, const double& price, const std::string& destination)
{
    if (PlaneCollection::getPlaneByID(planeId)->AssignedFlight())
		throw MyException("PlaneAlreadyAssignedToFlight");
    if (PlaneCollection::getPlaneByID(planeId)->getCon() != Condition::freePlane)
		throw MyException("PlaneInMaintenance");
    std::unique_ptr<Flight> newFlight = std::make_unique<Flight>(flightId, planeId, price, destination);
    FlightCatalog::addFlight(newFlight);
}


void Administrator::retrivePlaneFromHangar(const int& planeId, const std::string& hangarId)
{
    HangarCollection::getHangarById(hangarId)->removePlane(planeId);
}

double Administrator::flightRevenue(const std::string& flightId) const
{
    return FlightCatalog::getFlightRevenue(flightId);
}

void Administrator::printFleet(std::ostream& os, std::string airlineName) const
{
    for (const auto& i : PlaneCollection::getAllPlanes()) {
        if (i->getAirline() == airlineName) {
            os << *i;
        }
    }
}

void Administrator::airportReport(std::ostream& os) const
{
    AirportReportVisitor visitor;
    try {
        for (const auto& plane : PlaneCollection::getAllPlanes()) {
            plane->accept(visitor);
        }
    }
    catch (MyException& e) {
        std::cout << e.what() << '\n';
    }


    visitor.printReport(os);
}

void Administrator::auditAirline(std::ostream& os, std::string airlineName) const
{
    os << "Number of planes: \n";
    os << AirlineColl::getAirlineByName(airlineName)->getPlanesSize() << "\n";
    os << "Number of departed flights: \n";
    os << AirlineColl::getAirlineByName(airlineName)->getMadeFlights() << "\n";
    os << "Current balance: \n";
    os << AirlineColl::getAirlineByName(airlineName)->getBalance() << "\n";
}

Administrator::~Administrator()
{
    delete instance;
}

std::string Administrator::getPlaneType(const Plane* plane)
{
    if (dynamic_cast<const PassengerPlane*>(plane) != nullptr) {
        return "PassengerPlane";
    }
    if (dynamic_cast<const CargoPlane*>(plane) != nullptr) {
        return "CargoPlane";
    }
    if (dynamic_cast<const PrivateJet*>(plane) != nullptr) {
        return "PrivateJet";
    }
    throw MyException("UnknownPlaneType");
}

void Administrator::buyAircraft(std::string airline_name, std::string model, int capacity)
{
    try {
        PlaneFactory f(model, capacity);
        f.createPlane(airline_name);
    }
	catch (MyException& e) {
		std::cout << e.what() << '\n';
	}
}

void Administrator::registerAirline(std::string name, double balance)
{
    AirlineColl::addAirline(std::make_unique<Airline>(name, balance));
}

void Administrator::auditAirline(std::string airlineName) const
{
    int planeCount = 0;
    for (const auto& p : PlaneCollection::getAllPlanes()) {
        if (p->getAirline() == airlineName) {
            planeCount++;
        }
    }

    int completedFlights = 0;
    for (const auto& f : FlightCatalog::getAllFlights()) {
        const std::unique_ptr<Plane>& p = PlaneCollection::getPlaneByID(f->getPlaneId());
        if (p->getAirline() == airlineName && f->getStatus() == Status::Departed) {
            completedFlights++;
        }
    }

    double balance = AirlineColl::getAirlineByName(airlineName)->getBalance();
    std::cout << "Airline: " << airlineName << "\n";
    std::cout << "Fleet size: " << planeCount << "\n";
    std::cout << "Completed flights: " << completedFlights << "\n";
    std::cout << "Current balance: " << balance << "\n";
}

const void Administrator::help() const
{
    std::cout << "1.BuildRunway\n";
    std::cout << "2.BuildHangar\n";
    std::cout << "3.CloneAircraft\n";
    std::cout << "4.SendToHangar\n";
    std::cout << "5.ScheduleFlight\n";
    std::cout << "6.RetrieveFromHangar\n";
    std::cout << "7.CancelFlight\n";
    std::cout << "8.FlightRevenue\n";
    std::cout << "9.PrintFleet\n";
    std::cout << "10.AirportReport\n";
    std::cout << "11.AuditAirline\n";
    std::cout << "12.BuyAircraft\n";
    std::cout << "13.RegisterAirline\n";
    std::cout << "14.CloseRunway\n";
    std::cout << "15.ChangeWeather\n";
    std::cout << "16.Logout\n";
    std::cout << "17.Save\n";
    std::cout << "18.Load\n";
    std::cout << "19.Exit\n";
}

std::unique_ptr<User> Administrator::clone() const
{
    throw MyException("CannotCopyThis");
}

void Administrator::print(std::ostream& os) const
{
    os << "Name: " << name << "\n";
    os << "Password: " << password << "\n";
    os << "Type: Administrator" << "\n";
}
