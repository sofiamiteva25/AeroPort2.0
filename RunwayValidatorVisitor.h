#pragma once
#include "IRunwayValidatorVisitor.h"
class MyException;
class RunwayValidatorVisitor : public IRunwayValidatorVisitor {
    const Runway& runway;
    static unsigned int MIN_PASSENGER;
    static unsigned int MIN_CARGO;
    static unsigned int MIN_PRIVATE;
    void checkRunwayFree() const;
    void checkLength(unsigned int required, const std::string& planeType) const;

public:
    RunwayValidatorVisitor(const Runway& runway) : runway(runway) {}
    void visit(const PassengerPlane&) override;
    void visit(const CargoPlane&) override;
    void visit(const PrivateJet&) override;
};
