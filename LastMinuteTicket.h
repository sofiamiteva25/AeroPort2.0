#pragma once
#include "Ticket.h"
#include "TicketStrategy.h"

class LastMinuteTicket : public Ticket, public TicketStrategy {
public:
	LastMinuteTicket(int id, const std::string& owner, const std::string& flightID, double paidAmount);
	double calculatePrice(double basePrice) const override;
	bool canRefund() const override;
	std::unique_ptr<Ticket> clone() const override;
	bool canUpgrade() const override;
};
