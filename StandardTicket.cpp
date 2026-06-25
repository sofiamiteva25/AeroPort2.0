#include "StandardTicket.h"

StandardTicket::StandardTicket(int id,const std::string& owner, const std::string& flightID, double paidAmount)
    :Ticket(id, owner, flightID)
{
    this->paidAmount = paidAmount;
    this -> luggageAmount = LuggageStandart;
}

double StandardTicket::calculatePrice(double basePrice) const
{
    return basePrice;
}

bool StandardTicket::canRefund() const
{
    return true;
}

std::unique_ptr<Ticket> StandardTicket::clone() const
{
    return std::make_unique<StandardTicket>(*this);
}

bool StandardTicket::canUpgrade() const
{
    return true;
}
