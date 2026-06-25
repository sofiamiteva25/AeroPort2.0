#pragma once
class TicketStrategy {
public:
	virtual ~TicketStrategy() = default;
	virtual double calculatePrice(double basePrice) const = 0;
};
