#pragma once
#include <string>
#include "IDispatchCommand.h"
#include <memory>
#include <algorithm>

class FreeRunwayCommand : public IDispatchCommand {
    int runwayId;
    std::string savedFlightId;
    int         savedPlaneId = -1;

public:
    FreeRunwayCommand(int runwayId)
        : runwayId(runwayId) {
    }

    void execute() override;
    void undo()    override;
    std::unique_ptr<IDispatchCommand> clone() const override;
};
