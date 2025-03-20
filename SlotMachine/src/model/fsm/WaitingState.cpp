#include "WaitingState.h"
#include "SpinningState.h"
#include "../../utils/Logger.h"

std::unique_ptr<IState> WaitingState::buttonPressed(SlotMachine& machine) {
	machine.start();
	Logger::getInstance() << Logger::MODEL << Logger::INFO << "button pressed >> Spinning state\n";

	return std::make_unique<SpinningState>();
}

std::unique_ptr<IState> WaitingState::update(SlotMachine& machine) {
	return nullptr;
}

bool WaitingState::active() const {
	return false;
}
