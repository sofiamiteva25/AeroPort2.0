#pragma once
#include "Ticket.h"

class TicketFactory {
	std::string ticketOwner;
	std::string flightID;
	std::string type;
	double amount;
	static int count;
public:
	

	TicketFactory(const std::string& ticketOwner, const std::string& flightID, const std::string& type);
	std::unique_ptr<Ticket> createTicket();
};
