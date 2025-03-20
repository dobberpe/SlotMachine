#pragma once

#include "IState.h"

class ScoringState : public IState {
public:
    std::unique_ptr<IState> buttonPressed(SlotMachine& machine, SMWindow& window) override;
    
    std::unique_ptr<IState> update(SlotMachine& machine, SMWindow& window) override;
};

