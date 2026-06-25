#pragma once
#include <iostream>
class PassengerPlane;
class CargoPlane;
class PrivateJet;

class AirportReport
{
public:
    virtual void visit(PassengerPlane& p) = 0;
    virtual void visit(CargoPlane& p) = 0;
    virtual void visit(PrivateJet& p) = 0;
    virtual ~AirportReport() = default;
};
