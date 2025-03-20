#include "StoppingState.h"
#include "ScoringState.h"
#include "../../utils/Logger.h"

std::unique_ptr<IState> StoppingState::buttonPressed(SlotMachine& machine) {
	return nullptr;
}

std::unique_ptr<IState> StoppingState::update(SlotMachine& machine) {

	if (machine.spin()) {
		Logger::getInstance() << Logger::MODEL << Logger::INFO << "Scoring state\n";
		return std::make_unique<ScoringState>();
	}
	return nullptr;
}

bool StoppingState::active() const {
	return false;
}
