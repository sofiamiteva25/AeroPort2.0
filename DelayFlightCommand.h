#pragma once
#include <string>
#include "IDispatchCommand.h"
#include "Flight.h"
#include <memory>
#include <algorithm>

class DelayFlightCommand : public IDispatchCommand {
    std::string flightId;
    std::string reason;

    Status previousStatus = Status::Scheduled;

public:
    DelayFlightCommand(const std::string& flightId, const std::string& reason)
        : flightId(flightId), reason(reason) {
    }

    void execute() override;
    void undo()    override;
    std::unique_ptr<IDispatchCommand> clone() const override;
};
