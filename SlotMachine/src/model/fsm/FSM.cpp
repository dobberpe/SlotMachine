#include "FSM.h"
#include "WaitingState.h"

#include <iostream>

FSM::FSM() : state(std::make_unique<WaitingState>()) {}

void FSM::buttonPressed(SlotMachine& machine) {
	std::unique_ptr<IState> newState = state->buttonPressed(machine);

	if (newState) {
		std::cout << "new state by press\n";
		state = std::move(newState);
	}
}

void FSM::update(SlotMachine& machine) {
	std::unique_ptr<IState> newState = state->update(machine);

	if (newState) {
		std::cout << "new state by update\n";
		state = std::move(newState);
	}
}
