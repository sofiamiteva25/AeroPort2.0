#include "ProjectSerializer.h"
#include "PlaneCollection.h"
#include "RunwayCollection.h"
#include "HangarCollection.h"
#include "FlightCatalog.h"
#include "TicketCatalog.h"
#include "AirlineColl.h"
#include "UserColl.h"
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include "StandardTicket.h"
#include "LastMinuteTicket.h"
#include "VIPTicket.h"
#include "Passenger.h"
#include "TraficControl.h"
#include "Airline.h"
#include "MyException.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

const char ProjectSerializer::SEP = '|';

void ProjectSerializer::save(const std::string& filepath)
{
    std::ofstream out(filepath);
    if (!out.is_open()) {
        std::cout << "Cannot open file: " << filepath << '\n';
        return;
    }

    out << "[AIRLINES]\n";
    try {
        for (const auto& a : AirlineColl::getAllAirlines())
            out << a->getName() << SEP << a->getBalance() << '\n';
    } catch (...) {}

    out << "[PLANES]\n";
    try {
        for (const auto& p : PlaneCollection::getAllPlanes()) {
            std::string type = "PassengerPlane";
            if      (dynamic_cast<CargoPlane*>(p.get()))  type = "CargoPlane";
            else if (dynamic_cast<PrivateJet*>(p.get()))  type = "PrivateJet";
            out << type             << SEP
                << p->getID()      << SEP
                << p->getCap()     << SEP
                << p->getAirline() << SEP
                << static_cast<int>(p->getCon()) << SEP
                << p->getFlight()  << SEP
                << p->getTax()     << '\n';
        }
    } catch (...) {}

    out << "[RUNWAYS]\n";
    try {
        for (const auto& r : RunwayCollection::getAllRunways()) {
            out << r->getID()     << SEP
                << r->getLength() << SEP
                << (r->hasILS()       ? 1 : 0) << SEP
                << (r->hasHeavyDuty() ? 1 : 0) << SEP
                << (r->hasVIP()       ? 1 : 0) << SEP
                << static_cast<int>(r->getStatus()) << SEP
                << r->getPlaneOnRunway() << '\n';
        }
    } catch (...) {}

    out << "[HANGARS]\n";
    try {
        for (const auto& h : HangarCollection::getAllHangars()) {
            out << h->getId()       << SEP
                << h->getCapacity() << SEP
                << h->getTax()      << SEP;
            const auto& planes = h->getPlanesInHangar();
            for (std::size_t i = 0; i < planes.size(); ++i) {
                if (i) out << ',';
                out << planes[i];
            }
            out << '\n';
        }
    } catch (...) {}

    out << "[FLIGHTS]\n";
    try {
        for (const auto& f : FlightCatalog::getAllFlights()) {
            out << f->getID()          << SEP
                << f->getPlaneId()     << SEP
                << f->getDestination() << SEP
                << static_cast<int>(f->getStatus()) << SEP
                << f->getTicketPrice() << '\n';
        }
    } catch (...) {}

    out << "[TICKETS]\n";
    try {
        for (const auto& t : TicketCatalog::getAllTickets()) {
            std::string type = "Standard";
            if      (dynamic_cast<VIPTicket*>        (t.get())) type = "VIP";
            else if (dynamic_cast<LastMinuteTicket*> (t.get())) type = "LastMinute";
            out << type                  << SEP
                << t->getID()            << SEP
                << t->getTicketOwner()   << SEP
                << t->getFlightID()      << SEP
                << t->getPaidAmount()    << SEP
                << t->getLuggageAmount() << '\n';
        }
    } catch (...) {}

    out << "[USERS]\n";
    try {
        for (const auto& u : UserColl::getAllUsers()) {
            if (auto* p = dynamic_cast<Passenger*>(u.get())) {
                out << "Passenger" << SEP << p->getName() << SEP
                    << p->getPassword() << SEP << p->getBalance() << '\n';
            } else {
                out << "TrafficControl" << SEP << u->getName() << SEP
                    << u->getPassword() << '\n';
            }
        }
    } catch (...) {}

    out.flush();
    out.close();
    std::cout << "Saved to \"" << filepath << "\"\n";
}

void ProjectSerializer::load(const std::string& filepath)
{
    std::ifstream in(filepath);
    if (!in.is_open()) {
        std::cout << "Cannot open file: " << filepath << '\n';
        return;
    }

    PlaneCollection::reset();
    FlightCatalog::resetFlights();
    TicketCatalog::resetTickets();
    AirlineColl::airlineReset();
    HangarCollection::hangarReset();

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if      (line == "[PLANES]")   loadPlanes(in);
        else if (line == "[RUNWAYS]")  loadRunways(in);
        else if (line == "[HANGARS]")  loadHangars(in);
        else if (line == "[FLIGHTS]")  loadFlights(in);
        else if (line == "[TICKETS]")  loadTickets(in);
        else if (line == "[AIRLINES]") loadAirlines(in);
        else if (line == "[USERS]")    loadUsers(in);
    }

    std::cout << "Loaded from \"" << filepath << "\"\n";
}

void ProjectSerializer::printState(std::ostream& os)
{
    os << "=== Airport State ===\n";
    os << "-- Planes --\n";   PlaneCollection::printAllPlanes(os);
    os << "-- Runways --\n";  RunwayCollection::printAllRunways(os);
    os << "-- Hangars --\n";  HangarCollection::printAllHangars(os);
    os << "-- Flights --\n";  FlightCatalog::printAllFlights(os);
    os << "-- Tickets --\n";  TicketCatalog::printAllTickets(os);
}

std::vector<std::string> ProjectSerializer::readSection(std::ifstream& in)
{
    std::vector<std::string> lines;
    std::string line;
    std::streampos lastPos = in.tellg();

    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) { lastPos = in.tellg(); continue; }
        if (line.front() == '[') { in.seekg(lastPos); break; }
        lines.push_back(line);
        lastPos = in.tellg();
    }
    return lines;
}

std::vector<std::string> ProjectSerializer::split(const std::string& line)
{
    std::vector<std::string> parts;
    std::istringstream ss(line);
    std::string token;
    while (std::getline(ss, token, SEP))
        parts.push_back(token);
    return parts;
}

void ProjectSerializer::loadAirlines(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 2) continue;
        AirlineColl::addAirline(std::make_unique<Airline>(f[0], std::stod(f[1])));
    }
}

void ProjectSerializer::loadPlanes(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 7) continue;
        std::string type    = f[0];
        int         id      = std::stoi(f[1]);
        int         cap     = std::stoi(f[2]);
        std::string airline = f[3];
        int         cond    = std::stoi(f[4]);
        std::string flight  = f[5];

        std::unique_ptr<Plane> plane;
        if      (type == "CargoPlane") plane = std::make_unique<CargoPlane>   (id, cap, airline);
        else if (type == "PrivateJet") plane = std::make_unique<PrivateJet>   (id, cap, airline);
        else                           plane = std::make_unique<PassengerPlane>(id, cap, airline);

        plane->setCondition(static_cast<Condition>(cond));
        if (flight=="0") plane->assignFlight(flight);
        plane->setTax();
        PlaneCollection::addPlane(std::move(plane));
    }
}

void ProjectSerializer::loadRunways(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 7) continue;
        unsigned int length = static_cast<unsigned int>(std::stoul(f[1]));
        bool ils    = f[2] == "1";
        bool heavy  = f[3] == "1";
        bool vip    = f[4] == "1";
        int  status = std::stoi(f[5]);
        int  plane  = std::stoi(f[6]);

        auto builder = Runway::Builder{};
        builder.withLength(length);
        if (ils)   builder.withILS();
        if (heavy) builder.withHeavyDuty();
        if (vip)   builder.withVIPTerminal();
        auto r = builder.build();
        r->setStatus(static_cast<StatusRunway>(status));
        if (plane >= 0) r->setPlaneOnRunway(plane);
        RunwayCollection::addRunway(r);
    }
}

void ProjectSerializer::loadHangars(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 3) continue;
        auto hangar = std::make_unique<Hangar>(std::stoi(f[1]), std::stod(f[2]), f[0]);
        if (f.size() >= 4 && !f[3].empty()) {
            std::istringstream ss(f[3]);
            std::string token;
            while (std::getline(ss, token, ','))
                if (!token.empty()) hangar->addPlane(std::stoi(token));
        }
        HangarCollection::addHangar(std::move(hangar));
    }
}

void ProjectSerializer::loadFlights(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 5) continue;
        auto flight = std::make_unique<Flight>(f[0], std::stoi(f[1]), std::stod(f[4]), f[2]);
        flight->setStatus(static_cast<Status>(std::stoi(f[3])));
        FlightCatalog::addFlight(flight);
    }
}

void ProjectSerializer::loadTickets(std::ifstream& in)
{
    try {
        for (const auto& line : readSection(in)) {
            auto f = split(line);
            if (f.size() < 6) continue;
            std::string type = f[0];
            int         id = std::stoi(f[1]);
            std::string owner = f[2];
            std::string flight = f[3];
            double      paid = std::stod(f[4]);
            int         lug = std::stoi(f[5]);

            std::unique_ptr<Ticket> ticket;
            if (type == "VIP")        ticket = std::make_unique<VIPTicket>(id, owner, flight, paid);
            else if (type == "LastMinute") ticket = std::make_unique<LastMinuteTicket>(id, owner, flight, paid);
            else                           ticket = std::make_unique<StandardTicket>(id, owner, flight, paid);
            ticket->addLuggage(lug);
            TicketCatalog::addTicket(std::move(ticket));
        }
    }
        catch (...) {
            std::cout << "Error loading tickets. Some tickets may not be loaded correctly.\n";
        }
}

void ProjectSerializer::loadUsers(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 3) continue;
        if (f[0] == "TrafficControl") {
            UserColl::addUser(std::make_unique<TrafficControl>(f[1], f[2]));
        } else {
            double balance = (f.size() >= 4) ? std::stod(f[3]) : 0.0;
            UserColl::addUser(std::make_unique<Passenger>(f[1], f[2], balance));
        }
    }
}
