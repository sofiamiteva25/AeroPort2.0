#include "VIPTicket.h"

VIPTicket::VIPTicket(int id, const std::string& owner, const std::string& flightID, double paidAmount)
    :Ticket(id, owner, flightID)
{
    this->paidAmount = paidAmount*2;
    this->luggageAmount = LuggageVIP;
}

double VIPTicket::calculatePrice(double basePrice) const
{
    return basePrice*2 + (luggageAmount-LuggageVIP)*5;
}

bool VIPTicket::canRefund() const
{
    return true;
}

std::unique_ptr<Ticket> VIPTicket::clone() const
{
    return std::make_unique<VIPTicket>(*this);
}

bool VIPTicket::canUpgrade() const
{
    return false;
}
