#include "SpinningState.h"
#include "StoppingState.h"
#include "../../utils/Logger.h"

#include <iostream>

std::unique_ptr<IState> SpinningState::buttonPressed(SlotMachine& machine,
	SMWindow& window, bool spin) {

	if (!spin) {
		machine.stop();
		machine.spin();

		window.pressStopButton();

		Logger::getInstance() <<	Logger::CONTROLLER <<
									Logger::INFO <<
									"button pressed >> Stopping state\n";

		return std::make_unique<StoppingState>();
	}

	return nullptr;
}

std::unique_ptr<IState> SpinningState::update(SlotMachine& machine,
	SMWindow& window) {

	if (machine.spin()) {
		Logger::getInstance() <<	Logger::CONTROLLER <<
									Logger::INFO <<
									"Stopping state\n";

		return std::make_unique<StoppingState>();
	}

	if (window.spinButtonInPressedState()) {
		window.unpressSpinButton();
	}

	window.updateWheels(machine.getPositions());
	window.draw();

	return nullptr;
}