#pragma once

#include "../../model/SlotMachine.h"
#include "../../view/SMWindow.h"

#include <memory>

class IState {
public:
    virtual ~IState() = default;

    virtual std::unique_ptr<IState> buttonPressed(SlotMachine& machine,
        SMWindow& window, bool spin) = 0;
    
    virtual std::unique_ptr<IState> update(SlotMachine& machine,
        SMWindow& window) = 0;
};

