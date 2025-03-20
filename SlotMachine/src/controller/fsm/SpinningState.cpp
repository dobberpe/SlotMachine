#include "SpinningState.h"
#include "StoppingState.h"
#include "../../utils/Logger.h"

#include <iostream>

std::unique_ptr<IState> SpinningState::buttonPressed(SlotMachine& machine, SMWindow& window) {
	machine.stop();
	machine.spin();

	window.updateButton(true);

	Logger::getInstance() << Logger::MODEL << Logger::INFO << "button pressed >> Stopping state\n";

	return std::make_unique<StoppingState>();
}

std::unique_ptr<IState> SpinningState::update(SlotMachine& machine, SMWindow& window) {
	if (machine.spin()) {
		Logger::getInstance() << Logger::MODEL << Logger::INFO << "Stopping state\n";
		window.updateButton(true);
		return std::make_unique<StoppingState>();
	}

	window.updateWheels(machine.getPositions());
	window.draw();

	return nullptr;
}