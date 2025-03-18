#pragma once

#include <memory>

#include "../SlotMachine.h"

class IState {
public:
    virtual ~IState() = default;
    virtual std::unique_ptr<IState> buttonPressed(SlotMachine& machine) = 0;
    virtual std::unique_ptr<IState> update(SlotMachine& machine) = 0;
};

