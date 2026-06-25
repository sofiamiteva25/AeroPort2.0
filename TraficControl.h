#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
#include "Flight.h"
#include "Runway.h"
#include "AirlineColl.h"
#include "RunwayValidatorVisitor.h"
#include "User.h"
#include "IDispatchCommand.h"
class MyException;
class TrafficControl: public User {
    std::vector<std::unique_ptr<IDispatchCommand>> history;

    void executeAndRecord(std::unique_ptr<IDispatchCommand> cmd);

public:
    TrafficControl(const std::string& name, const std::string& password)
        : User(name, password) {
    }
    TrafficControl(const TrafficControl& other);
    void listAirspace()  const;
    void listRunways()   const;
    void assignRunway(const std::string& flightId, int runwayId);
    void delayFlight(const std::string& flightId, const std::string& reason);
    void freeRunway(int runwayId);
    void undo();
    void help() override;
    void print(std::ostream& os) const override;
    std::unique_ptr<User> clone() const override;
};
