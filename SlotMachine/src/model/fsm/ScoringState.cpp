#include "ScoringState.h"
#include "WaitingState.h"

std::unique_ptr<IState> ScoringState::buttonPressed(SlotMachine& machine) {
	return nullptr;
}

std::unique_ptr<IState> ScoringState::update(SlotMachine& machine) {
	// считаем
	return std::unique_ptr<WaitingState>();
}
