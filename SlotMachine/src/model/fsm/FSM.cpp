#include "FSM.h"
#include "WaitingState.h"
#include "../../utils/Logger.h"

FSM::FSM() : state(std::make_unique<WaitingState>()) {
	Logger::getInstance() << Logger::MODEL << Logger::INFO << "Waiting state\n";
}

void FSM::buttonPressed(SlotMachine& machine) {
	std::unique_ptr<IState> newState = state->buttonPressed(machine);

	if (newState) {
		state = std::move(newState);
	}
}

void FSM::update(SlotMachine& machine) {
	std::unique_ptr<IState> newState = state->update(machine);

	if (newState) {
		state = std::move(newState);
	}
}

bool FSM::active() const {
	return state->active();
}
