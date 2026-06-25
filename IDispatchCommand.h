#pragma once
#include <memory>
class IDispatchCommand {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~IDispatchCommand() = default;
    virtual std::unique_ptr<IDispatchCommand> clone() const = 0;
};
