#pragma once

#include "IState.h"

class FSM {
public:
	FSM();
	
	~FSM() = default;
	
	void buttonPressed(SlotMachine& machine, SMWindow& window);
	
	void update(SlotMachine& machine, SMWindow& window);

private:
	std::unique_ptr<IState> state;
};

