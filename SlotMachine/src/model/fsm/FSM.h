#pragma once

#include "IState.h"

class FSM {
public:
	FSM();
	
	~FSM() = default;
	
	void buttonPressed(SlotMachine& machine);
	
	void update(SlotMachine& machine);

	bool active() const;

private:
	std::unique_ptr<IState> state;
};

