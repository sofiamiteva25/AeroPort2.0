#include "Passenger.h"
#include "FlightCatalog.h"
#include "TicketCatalog.h"
#include "TicketFactory.h"
#include "UserColl.h"
#include "MyException.h"
double& Passenger::addFunds(const double& amount)
{
    if (amount > 0) {
        balance += amount;
    }
    return balance;
}

std::vector<std::unique_ptr<Flight>> Passenger::listFlightByDestination(const std::string& _destination)
{   
    std::vector<std::unique_ptr<Flight>> flightsByDest;
    for (auto& i : FlightCatalog::getFlightsByDestination(_destination)) {
        if (i->getStatus() == Status::Scheduled || i->getStatus() == Status::Delayed) {
            flightsByDest.push_back(std::move(i));
        }
    }
    if (flightsByDest.size() == 0) {
        throw MyException("NoFlightsToDestination");
    }
    return flightsByDest;

}

std::vector<std::unique_ptr<Flight>> Passenger::filterFlightsByPrice(const double& maxPrice)
{
    std::vector<std::unique_ptr<Flight>> flightsByPrice =  FlightCatalog::getFlightsByPrice(maxPrice);
    return flightsByPrice;
}

std::vector<std::unique_ptr<Ticket>> Passenger::myTickets()
{
    return TicketCatalog::getTicketByOwner(this->name);
}

void Passenger::bookTicket(const std::string flightId, const std::string type)
{
    TicketFactory t(this->getName(), flightId, type);
    std::unique_ptr<Ticket> ticket = t.createTicket();
    this->addFunds(-ticket->getPaidAmount());
}

void Passenger::upgradeTicket(const std::string flightId, std::string newType)
{
    std::unique_ptr<Ticket> found = nullptr;
    for (auto& i : TicketCatalog::getAllTickets()) {
        if (i->getFlightID() == flightId && i->getTicketOwner() == this->name) {
            found = i->clone();
            break;
        }
    }
    if (!found)
        throw MyException("NoTicketFound");
    if (!found->canUpgrade())
        throw MyException("CannotRefund");

    double oldAmount = found->getPaidAmount();
    int oldId = found->getID();

    TicketCatalog::removeTicket(oldId);
    TicketFactory factory(found->getTicketOwner(), flightId, newType);
    factory.createTicket();
    double newAmount = 0;
    for (const auto& i : TicketCatalog::getTicketsByFlightId(flightId)) {
        if (i->getTicketOwner() == found->getTicketOwner()) {
            newAmount = i->getPaidAmount();
            break;
        }
    }

    if (balance < 0) {
        TicketCatalog::removeTicket(TicketCatalog::getTicketsByFlightId(flightId).back()->getID());
        TicketFactory rollback(found->getTicketOwner(), flightId, "Standard");
        rollback.createTicket();
        balance += oldAmount;
        throw MyException("NoEnoghtBalanceForUpgrade");
    }
}

void Passenger::cancelTicket(const std::string& flightId)
{
    for (const auto& i:TicketCatalog::getTicketByOwner(name)) {
        if (i->getFlightID() == flightId) {
            if (i->canRefund()) {
                this->addFunds(i->getPaidAmount());
                TicketCatalog::removeTicket(i->getID());
                return;
            }
        }
    }
    throw MyException("CannotRefund");
}

void Passenger::addLuggage(const std::string& flightId, const int& luggageAmount)
{
    for (auto& i : TicketCatalog::getAllTickets()) {
        if (i->getFlightID() == flightId && i->getTicketOwner() == this->name) {
            i->addLuggage(luggageAmount);
            return;
        }
    }
    throw MyException("NoTicketFound");
}

const double Passenger::getBalance() const
{
    return balance;
}

void Passenger::refundTicket(const std::string& flightId)
{
    for (const auto& i : TicketCatalog::getTicketByOwner(this->name)) {
        if (i->getFlightID() == flightId) {
                addFunds(i->getPaidAmount());
                TicketCatalog::removeTicket(i->getID());
                return;
        }
    }
}

void Passenger::help()
{
    std::cout << "1.AddFunds\n";
    std::cout << "2.ListFlights\n";
    std::cout << "3.FilterFlights\n";
    std::cout << "4.BookTicket\n";
    std::cout << "5.UpgradeTicket\n";
    std::cout << "6.AddBaggage\n";
    std::cout << "7.CancelTicket\n";
    std::cout << "8.MyTicket\n";
}

void Passenger::print(std::ostream& os) const
{
    os << "Name: " << name << "\n";
    os << "Password: " << password << "\n";
    os << "Type: Passenger" << "\n";
}

std::unique_ptr<User> Passenger::clone() const
{
    return std::make_unique<Passenger>(*this);
}
