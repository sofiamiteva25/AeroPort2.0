#include "TicketCatalog.h"
#include "MyException.h"
std::vector<std::unique_ptr<Ticket>> TicketCatalog::tickets;

std::vector<std::unique_ptr<Ticket>>& TicketCatalog::getAllTickets()
{
    return tickets;
}

std::vector<std::unique_ptr<Ticket>> TicketCatalog::getTicketByOwner(const std::string& _owner)
{
    std::vector<std::unique_ptr<Ticket>> ownedTickets;
    for (const auto& i : tickets) {
        if (i->getTicketOwner() == _owner) {
            ownedTickets.push_back(i->clone());
        }
    }
    if (ownedTickets.size() > 0) {
        return ownedTickets;
    }
    throw MyException("NoTicketWithThisOwner");
}

void TicketCatalog::addTicket(std::unique_ptr<Ticket> ticket)
{
    for (const auto& i : tickets) {
        if (i->getID() == ticket->getID()) {
            throw MyException("TicketAlreadyAdded");
            return;
        }
    }
    tickets.push_back(std::move(ticket));
}

std::vector<std::unique_ptr<Ticket>> TicketCatalog::getTicketsByFlightId(const std::string& flightID)
{
    std::vector<std::unique_ptr<Ticket>> flightTickets;
    for (const auto& i : tickets) {
        if (i->getFlightID() == flightID) {
            flightTickets.push_back(i->clone());
        }
    }
    if (flightTickets.size() > 0) {
        return flightTickets;
    }
    throw MyException("NoTicketWithThisId");
    
}

void TicketCatalog::removeTicket(const int ID)
{
    auto it = std::find_if(tickets.begin(), tickets.end(), [&ID](std::unique_ptr<Ticket>& a) {
        return a->getID() == ID;
        });
    if (it != tickets.end()) {
        tickets.erase(it);
        return;
    }
    throw MyException("NoTicketWithThisId");
}


double TicketCatalog::allPaidAmount(const std::string& flightId)
{
    double price = 0;
    std::vector<std::unique_ptr<Ticket>> flightT =TicketCatalog::getTicketsByFlightId(flightId);
    for (const auto& i : flightT) {
        price += i->getPaidAmount();
    }
    return price;
}

void TicketCatalog::resetTickets()
{
    tickets.clear();
}

void TicketCatalog::printAllTickets(std::ostream& os)
{
    for (const auto& i : tickets) {
        os << *i;
    }
}
