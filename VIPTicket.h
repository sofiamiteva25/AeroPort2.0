#pragma once
#include "Ticket.h"
#include "TicketStrategy.h"

class VIPTicket : public Ticket, public TicketStrategy {
public:
	VIPTicket(int id, const std::string& owner, const std::string& flightID, double paidAmount);
	double calculatePrice(double basePrice) const override;
	bool canRefund() const override;
	std::unique_ptr<Ticket> clone() const override;
	bool canUpgrade() const override;
};
