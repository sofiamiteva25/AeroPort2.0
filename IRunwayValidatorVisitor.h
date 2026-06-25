#pragma once
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include "Runway.h"
class IRunwayValidatorVisitor {
public:
    virtual void visit(const PassengerPlane& plane) = 0;
    virtual void visit(const CargoPlane& plane) = 0;
    virtual void visit(const PrivateJet& plane) = 0;
    virtual ~IRunwayValidatorVisitor() = default;
};
