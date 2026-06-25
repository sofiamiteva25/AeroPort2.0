#include "ProjectSerializer.h"


#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


void ProjectSerializer::save(const std::string& filepath)
{
    std::ofstream out(filepath);
    if (!out.is_open())
        throw MyException("CannotOpenFile");

    savePlanes(out);
    saveRunways(out);
    saveHangars(out);
    saveFlights(out);
    saveTickets(out);
    saveAirlines(out);
    saveUsers(out);
}

void ProjectSerializer::load(const std::string& filepath)
{
    std::ifstream in(filepath);
    if (!in.is_open())
        throw MyException("CannotOpenFile");
    PlaneCollection::reset();
    FlightCatalog::resetFlights();
    TicketCatalog::resetTickets();

    std::string line;
    while (std::getline(in, line)) {
        if (line == "[PLANES]")   loadPlanes(in);
        else if (line == "[RUNWAYS]")  loadRunways(in);
        else if (line == "[HANGARS]")  loadHangars(in);
        else if (line == "[FLIGHTS]")  loadFlights(in);
        else if (line == "[TICKETS]")  loadTickets(in);
        else if (line == "[AIRLINES]") loadAirlines(in);
        else if (line == "[USERS]")    loadUsers(in);
    }

    std::cout << "[ProjectSerializer] Loaded from \"" << filepath << "\"\n";
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
void ProjectSerializer::savePlanes(std::ofstream& out)
{
    out << "[PLANES]\n";
    for (const auto& p : PlaneCollection::getAllPlanes()) {
        std::string type = "PassengerPlane";
        if (dynamic_cast<CargoPlane*> (p.get())) type = "CargoPlane";
        else if (dynamic_cast<PrivateJet*> (p.get())) type = "PrivateJet";

        out << type << SEP
            << p->getID() << SEP
            << p->getCap() << SEP
            << p->getAirline() << SEP
            << static_cast<int>(p->getCon()) << SEP
            << p->getFlight() << SEP
            << p->getTax() << '\n';
    }
}
void ProjectSerializer::saveRunways(std::ofstream& out)
{
    out << "[RUNWAYS]\n";
    for (const auto& r : RunwayCollection::getAllRunways()) {
        out << r->getID() << SEP
            << r->getLength() << SEP
            << (r->hasILS() ? 1 : 0) << SEP
            << (r->hasHeavyDuty() ? 1 : 0) << SEP
            << (r->hasVIP() ? 1 : 0) << SEP
            << static_cast<int>(r->getStatus()) << SEP
            << r->getPlaneOnRunway() << '\n';
    }
}

void ProjectSerializer::saveHangars(std::ofstream& out)
{
    out << "[HANGARS]\n";
    for (const auto& h : HangarCollection::getAllHangars()) {
        out << h->getId() << SEP
            << h->getCapacity() << SEP
            << h->getTax() << SEP;

        const auto& planes = h->getPlanesInHangar();
        for (std::size_t i = 0; i < planes.size(); ++i) {
            if (i) out << ',';
            out << planes[i];
        }
        out << '\n';
    }
}

void ProjectSerializer::saveFlights(std::ofstream& out)
{
    out << "[FLIGHTS]\n";
    for (const auto& f : FlightCatalog::getAllFlights()) {
        out << f->getID() << SEP
            << f->getPlaneId() << SEP
            << f->getDestination() << SEP
            << static_cast<int>(f->getStatus()) << SEP
            << f->getTicketPrice() << '\n';
    }
}

void ProjectSerializer::saveTickets(std::ofstream& out)
{
    out << "[TICKETS]\n";
    for (const auto& t : TicketCatalog::getAllTickets()) {
        std::string type = "Standard";
        if (dynamic_cast<VIPTicket*>        (t.get())) type = "VIP";
        else if (dynamic_cast<LastMinuteTicket*> (t.get())) type = "LastMinute";

        out << type << SEP
            << t->getID() << SEP
            << t->getTicketOwner() << SEP
            << t->getFlightID() << SEP
            << t->getPaidAmount() << SEP
            << t->getLuggageAmount() << '\n';
    }
}

void ProjectSerializer::saveAirlines(std::ofstream& out)
{
    out << "[AIRLINES]\n";
    for (const auto& a : AirlineColl::getAllAirlines())
        out << a->getName() << SEP << a->getBalance() << '\n';
}

void ProjectSerializer::saveUsers(std::ofstream& out)
{
    out << "[USERS]\n";
    for (const auto& u : UserColl::getAllUsers()) {
        std::string type = "TrafficControl";
        if (auto* p = dynamic_cast<Passenger*>(u.get())) {
            out << "Passenger" << SEP << p->getName() << SEP
                << p->getPassword() << SEP << p->getBalance() << '\n';
        }
        else {
            out << type << SEP << u->getName() << SEP << u->getPassword() << '\n';
        }
    }
}

std::vector<std::string> ProjectSerializer::readSection(std::ifstream& in)
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (line.front() == '[') {
            in.seekg(-(static_cast<std::streamoff>(line.size()) + 1), std::ios::cur);
            break;
        }
        lines.push_back(line);
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

void ProjectSerializer::loadPlanes(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 7) continue;

        std::string type = f[0];
        int         id = std::stoi(f[1]);
        int         cap = std::stoi(f[2]);
        std::string airline = f[3];
        int         cond = std::stoi(f[4]);
        std::string flight = f[5];

        std::unique_ptr<Plane> plane;
        if (type == "CargoPlane") plane = std::make_unique<CargoPlane>(id, cap, airline);
        else if (type == "PrivateJet") plane = std::make_unique<PrivateJet>(id, cap, airline);
        else                           plane = std::make_unique<PassengerPlane>(id, cap, airline);

        plane->setCondition(static_cast<Condition>(cond));
        if (!flight.empty()) plane->assignFlight(flight);
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
        bool ils = f[2] == "1";
        bool heavy = f[3] == "1";
        bool vip = f[4] == "1";
        int  status = std::stoi(f[5]);
        int  plane = std::stoi(f[6]);

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

        std::string id = f[0];
        int  capacity = std::stoi(f[1]);
        double tax = std::stod(f[2]);

        auto hangar = std::make_unique<Hangar>(capacity, tax, id);

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

        std::string id = f[0];
        int  planeId = std::stoi(f[1]);
        std::string dest = f[2];
        int  status = std::stoi(f[3]);
        double price = std::stod(f[4]);

        auto flight = std::make_unique<Flight>(id, planeId, price, dest);
        flight->setStatus(static_cast<Status>(status));
        FlightCatalog::addFlight(flight);
    }
}

void ProjectSerializer::loadTickets(std::ifstream& in)
{
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

        try { FlightCatalog::getFlightByID(flight)->addTicket(id); }
        catch (...) {}
    }
}

void ProjectSerializer::loadAirlines(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 2) continue;
        AirlineColl::addAirline(std::make_unique<Airline>(f[0], std::stod(f[1])));
    }
}

void ProjectSerializer::loadUsers(std::ifstream& in)
{
    for (const auto& line : readSection(in)) {
        auto f = split(line);
        if (f.size() < 3) continue;

        std::string type = f[0];
        std::string name = f[1];
        std::string pass = f[2];

        if (type == "TrafficControl") {
            UserColl::addUser(std::make_unique<TrafficControl>(name, pass));
        }
        else {
            double balance = (f.size() >= 4) ? std::stod(f[3]) : 0.0;
            UserColl::addUser(std::make_unique<Passenger>(name, pass, balance));
        }
    }
}