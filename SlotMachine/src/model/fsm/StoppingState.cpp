#include "StoppingState.h"
#include "ScoringState.h"

std::unique_ptr<IState> StoppingState::buttonPressed(SlotMachine& machine) {
	return nullptr;
}

std::unique_ptr<IState> StoppingState::update(SlotMachine& machine) {
	return machine.spin() ? std::make_unique<ScoringState>() : nullptr;
}
