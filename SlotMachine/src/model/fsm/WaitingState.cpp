#include "WaitingState.h"
#include "SpinningState.h"

std::unique_ptr<IState> WaitingState::buttonPressed(SlotMachine& machine) {
	machine.start();
	return std::make_unique<SpinningState>();
}

std::unique_ptr<IState> WaitingState::update(SlotMachine& machine) {
	return nullptr;
}
