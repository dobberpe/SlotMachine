#include "AccelerationState.h"
#include "DecelerationState.h"

std::unique_ptr<IState> AccelerationState::buttonPressed(SlotMachine& machine) {
	return std::unique_ptr<DecelerationState>();
}

std::unique_ptr<IState> AccelerationState::update(SlotMachine& machine) {
	machine.spin();

	return machine.accelerate() ? std::unique_ptr<DecelerationState>() : nullptr;
}
