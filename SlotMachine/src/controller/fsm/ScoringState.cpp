#include "ScoringState.h"
#include "WaitingState.h"
#include "../../utils/Logger.h"

std::unique_ptr<IState> ScoringState::buttonPressed(SlotMachine& machine,
	SMWindow& window, bool spin) {

	return nullptr;
}

std::unique_ptr<IState> ScoringState::update(SlotMachine& machine,
	SMWindow& window) {

	window.updateScore(machine.getScore());
	window.draw();

	Logger::getInstance() <<	Logger::CONTROLLER <<
								Logger::INFO <<
								"Waiting state\n";

	return std::make_unique<WaitingState>();
}