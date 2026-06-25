#pragma once
#include "Ticket.h"

class TicketCatalog {
	static std::vector<std::unique_ptr<Ticket>> tickets;
public:
	static std::vector<std::unique_ptr<Ticket>>& getAllTickets();
	static std::vector<std::unique_ptr<Ticket>> getTicketByOwner(const std::string& _owner);
	static void addTicket(std::unique_ptr<Ticket> ticket);
	static std::vector<std::unique_ptr<Ticket>> getTicketsByFlightId(const std::string& flightID);
	static void removeTicket(const int ID);
	static double allPaidAmount(const std::string& flightId);
	static void resetTickets();
	static void printAllTickets(std::ostream& os);
};
