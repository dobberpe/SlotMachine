#include "SpinningState.h"
#include "StoppingState.h"
#include "../../utils/Logger.h"

#include <iostream>

std::unique_ptr<IState> SpinningState::buttonPressed(SlotMachine& machine) {
	Logger::getInstance() << Logger::MODEL << Logger::INFO << "button pressed >> Stopping state\n";
	machine.stop();
	machine.spin();

	return std::make_unique<StoppingState>();
}

std::unique_ptr<IState> SpinningState::update(SlotMachine& machine) {
	if (machine.spin()) {
		Logger::getInstance() << Logger::MODEL << Logger::INFO << "Stopping state\n";
		return std::make_unique<StoppingState>();
	}
	return nullptr;
}

bool SpinningState::active() const {
	return true;
}
