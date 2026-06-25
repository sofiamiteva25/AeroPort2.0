#include "Ticket.h"
#include "Person.h"
#include "FlightCatalog.h"
#include "MyException.h"
Ticket::Ticket(int id,const std::string& owner, const std::string& flightID)
{
    this->id = id;
    setTicketOwner(owner);
    setFlightID(flightID);
}

void Ticket::setFlightID(std::string flightID)
{
    for (const auto& i : FlightCatalog::getAllFlights()) {
        if (i->getID() == flightID) {
            this->flightID = flightID;
            return;
        }
    }
    throw MyException("NoFlightWithThisID");

}

void Ticket::setTicketOwner(const std::string owner)
{
    const auto& passengers = UserColl::getAllUsers();
    auto it = std::find_if(passengers.begin(), passengers.end(), [&owner](const std::unique_ptr<User>& p) {
        return p->getName() == owner;
        });
    if (it != passengers.end()) {
        this->ticketOwner = owner;
        return;
    }
    throw MyException("invalidName");

}

void Ticket::addLuggage(const int& amount)
{
    if (amount > 0) {
        this->luggageAmount += amount;
        this->paidAmount += amount * 5;
    }
}

const std::string Ticket::getTicketOwner() const
{
    return ticketOwner;
}

const int& Ticket::getID() const
{
    return id;
}

const std::string Ticket::getFlightID() const
{
    return flightID;
}

const double Ticket::getPaidAmount() const
{
    return paidAmount;
}

void Ticket::print(std::ostream& os) const
{
    os << "Id: " << id << "\n";
    os << "TicketOwner: " << ticketOwner << "\n";
    os << "FlightID: " << flightID << "\n";
    os << "PaidAmount: " << paidAmount << "\n";
    os << "LuggageAmount: " << luggageAmount << "\n";
}

std::ostream& operator<<(std::ostream& os, const Ticket& t)
{
    t.print(os);
    return os;
}
