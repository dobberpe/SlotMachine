#include "FSM.h"
#include "WaitingState.h"
#include "../../utils/Logger.h"

FSM::FSM() : state(std::make_unique<WaitingState>()) {

	Logger::getInstance() <<	Logger::CONTROLLER <<
								Logger::INFO <<
								"Waiting state\n";

}

void FSM::buttonPressed(SlotMachine& machine, SMWindow& window, bool spin) {

	std::unique_ptr<IState> newState = state->buttonPressed(machine, window,
		spin);

	if (newState) {
		state = std::move(newState);
	}
}

void FSM::update(SlotMachine& machine, SMWindow& window) {

	std::unique_ptr<IState> newState = state->update(machine, window);

	if (newState) {
		state = std::move(newState);
	}
}