#include "RunwayValidatorVisitor.h"
#include "MyException.h"
unsigned int RunwayValidatorVisitor::MIN_PASSENGER = 2000;
unsigned int RunwayValidatorVisitor::MIN_CARGO = 3000;
unsigned int RunwayValidatorVisitor::MIN_PRIVATE = 1000;

void RunwayValidatorVisitor::checkRunwayFree() const
{
    if (runway.getStatus() != StatusRunway::RunwayFree)
        throw MyException("RunwayNotFree");
}

void RunwayValidatorVisitor::checkLength(unsigned int required, const std::string& planeType) const
{
    if (runway.getLength() < required)
        throw MyException("RunwayNotSuitable");
}

void RunwayValidatorVisitor::visit(const PassengerPlane&)
{
    checkRunwayFree();
    checkLength(MIN_PASSENGER, "PassengerPlane");
    if (!runway.hasILS())
        throw MyException("RunwayNotSuitable");
}

void RunwayValidatorVisitor::visit(const CargoPlane&)
{
    checkRunwayFree();
    checkLength(MIN_CARGO, "CargoPlane");
    if (!runway.hasHeavyDuty())
        throw MyException("RunwayNotSuitable");
}

void RunwayValidatorVisitor::visit(const PrivateJet&)
{
    checkRunwayFree();
    checkLength(MIN_PRIVATE, "PrivateJet");
    if (!runway.hasVIP())
        throw MyException("RunwayNotSuitable");
}
