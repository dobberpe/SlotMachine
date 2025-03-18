#include "WaitingState.h"
#include "AccelerationState.h"

std::unique_ptr<IState> WaitingState::buttonPressed(SlotMachine& machine) {
	machine.start();
	return std::make_unique<AccelerationState>();
}

std::unique_ptr<IState> WaitingState::update(SlotMachine& machine) {
	return nullptr;
}
