#pragma once

#include "IState.h"

class FSM {
private:
	std::unique_ptr<IState> state;
public:
	FSM();
	~FSM() = default;
	void buttonPressed(SlotMachine& machine);
	void update(SlotMachine& machine);
};

