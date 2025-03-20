#pragma once

#include "IState.h"

class WaitingState : public IState {
public:
    std::unique_ptr<IState> buttonPressed(SlotMachine& machine, SMWindow& window) override;
    
    std::unique_ptr<IState> update(SlotMachine& machine, SMWindow& window) override;
};

