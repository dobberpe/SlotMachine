#include "SpinningState.h"
#include "StoppingState.h"
#include "ScoringState.h"

#include <iostream>

std::unique_ptr<IState> SpinningState::buttonPressed(SlotMachine& machine) {
	return std::make_unique<StoppingState>();
}

std::unique_ptr<IState> SpinningState::update(SlotMachine& machine) {
	return machine.spin() ? std::make_unique<ScoringState>() : nullptr;
}
