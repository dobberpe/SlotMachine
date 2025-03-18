#include "DecelerationState.h"
#include "AlignmentState.h"

std::unique_ptr<IState> DecelerationState::buttonPressed(SlotMachine& machine) {
	return nullptr;
}

std::unique_ptr<IState> DecelerationState::update(SlotMachine& machine) {
	machine.spin();

	return machine.decelerate() ? std::unique_ptr<AlignmentState>() : nullptr;
}
