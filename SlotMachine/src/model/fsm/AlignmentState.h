#pragma once

#include "IState.h"

class AlignmentState : public IState {
public:
    std::unique_ptr<IState> buttonPressed(SlotMachine& machine) override;
    std::unique_ptr<IState> update(SlotMachine& machine) override;
};

