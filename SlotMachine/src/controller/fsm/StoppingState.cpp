#include "StoppingState.h"
#include "ScoringState.h"
#include "../../utils/Logger.h"

std::unique_ptr<IState> StoppingState::buttonPressed(SlotMachine& machine,
	SMWindow& window, bool spin) {

	return nullptr;
}

std::unique_ptr<IState> StoppingState::update(SlotMachine& machine,
	SMWindow& window) {

	if (machine.spin()) {
		Logger::getInstance() <<	Logger::CONTROLLER <<
									Logger::INFO <<
									"Scoring state\n";

		return std::make_unique<ScoringState>();
	}

	if (window.stopButtonInPressedState()) {
		window.unpressStopButton();
	}

	window.updateWheels(machine.getPositions());
	window.draw();

	return nullptr;
}