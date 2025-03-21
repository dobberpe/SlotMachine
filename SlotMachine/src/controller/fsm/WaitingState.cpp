#include "WaitingState.h"
#include "SpinningState.h"
#include "../../utils/Logger.h"

std::unique_ptr<IState> WaitingState::buttonPressed(SlotMachine& machine,
	SMWindow& window, bool spin) {

	if (spin) {
		machine.start();

		window.pressSpinButton();

		Logger::getInstance() <<	Logger::CONTROLLER <<
									Logger::INFO <<
									"button pressed >> Spinning state\n";

		return std::make_unique<SpinningState>();
	}

	return nullptr;
}

std::unique_ptr<IState> WaitingState::update(SlotMachine& machine,
	SMWindow& window) {

	return nullptr;
}
