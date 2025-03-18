#include "FSM.h"
#include "WaitingState.h"

FSM::FSM() : state(std::make_unique<WaitingState>()) {}

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
