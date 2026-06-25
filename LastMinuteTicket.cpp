#include "LastMinuteTicket.h"

LastMinuteTicket::LastMinuteTicket(int id, const std::string& owner, const std::string& flightID, double paidAmount)
    :Ticket(id,owner, flightID)
{
    this->paidAmount = paidAmount/2;
    this->luggageAmount = LuggageLastMinute;
}

double LastMinuteTicket::calculatePrice(double basePrice) const
{

    return basePrice / 2 * luggageAmount*5;
}

bool LastMinuteTicket::canRefund() const
{
    return false;
}

std::unique_ptr<Ticket> LastMinuteTicket::clone() const
{
    return std::make_unique<LastMinuteTicket>(*this);
}

bool LastMinuteTicket::canUpgrade() const
{
    return false;
}
