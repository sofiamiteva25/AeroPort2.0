#pragma once
#include <string>
#include "IDispatchCommand.h"
#include <memory>
#include <algorithm>

class AssignRunwayCommand : public IDispatchCommand {
    std::string flightId;
    int         runwayId;
    int savedPlaneOnRunway = -1;

public:
    AssignRunwayCommand(const std::string& flightId, int runwayId)
        : flightId(flightId), runwayId(runwayId) 
    {
    }

    void execute() override;
    void undo()    override;
    std::unique_ptr<IDispatchCommand> clone() const override;
};
