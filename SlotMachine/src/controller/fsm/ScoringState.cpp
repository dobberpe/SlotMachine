#include "ScoringState.h"
#include "WaitingState.h"
#include "../../utils/Logger.h"

std::unique_ptr<IState> ScoringState::buttonPressed(SlotMachine& machine, SMWindow& window) {
	return nullptr;
}

std::unique_ptr<IState> ScoringState::update(SlotMachine& machine, SMWindow& window) {
	Logger::getInstance() << Logger::MODEL << Logger::INFO << "Waiting state\n";

	return std::make_unique<WaitingState>();
}