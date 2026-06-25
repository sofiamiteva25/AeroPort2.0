#include "TicketFactory.h"
#include "StandardTicket.h"
#include "LastMinuteTicket.h"
#include "VIPTicket.h"
#include "TicketCatalog.h"
#include "FlightCatalog.h"
#include "MyException.h"
int TicketFactory::count = 1;

TicketFactory::TicketFactory(const std::string& ticketOwner, const std::string& flightID, const std::string& type)
    : ticketOwner(ticketOwner), flightID(flightID), type(type)
{
    this->amount = FlightCatalog::getFlightByID(flightID)->getTicketAmount();
}

std::unique_ptr<Ticket> TicketFactory::createTicket()
{
    if (type == "Standard") {
        std::unique_ptr<StandardTicket> t =  std::make_unique<StandardTicket>(count, ticketOwner, flightID, amount);
        count++;
        TicketCatalog::addTicket(t->clone());
        return t;
    }
    if (type == "LastMinute") {
        std::unique_ptr<LastMinuteTicket> t = std::make_unique<LastMinuteTicket>(count, ticketOwner, flightID, amount);
        count++;
        TicketCatalog::addTicket(t->clone());
        return t;
    }
    if (type == "VIPTicket") {
        std::unique_ptr<VIPTicket> t = std::make_unique<VIPTicket>(count, ticketOwner, flightID, amount);
        count++;
        TicketCatalog::addTicket(t->clone());
        return t;
    }
    throw MyException("NotPossibleTicketType");
}
