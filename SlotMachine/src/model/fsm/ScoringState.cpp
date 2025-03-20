#include "ScoringState.h"
#include "WaitingState.h"
#include "../../utils/Logger.h"

std::unique_ptr<IState> ScoringState::buttonPressed(SlotMachine& machine) {
	return nullptr;
}

std::unique_ptr<IState> ScoringState::update(SlotMachine& machine) {
	Logger::getInstance() << Logger::MODEL << Logger::INFO << "Waiting state\n";
	return std::make_unique<WaitingState>();
}

bool ScoringState::active() const {
	return false;
}
