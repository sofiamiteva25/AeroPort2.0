#pragma once
#include "AirportReport.h"

class AirportReportVisitor : public AirportReport {
    double passengerTax = 0.0;
    double cargoTax = 0.0;
    double privateTax = 0.0;
    int    passengerCount = 0;
    int    cargoCount = 0;
    int    privateCount = 0;

public:
    void visit(PassengerPlane& p) override;
    void visit(CargoPlane& p) override;
    void visit(PrivateJet& p) override;
    void printReport(std::ostream& os) const;
    double getTotal() const;
};
