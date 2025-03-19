#pragma once

#include "../model/fsm/FSM.h"
#include "../view/SMWindow.h"

#include <memory>

class SMController {
public:
	SMController();
	~SMController() = default;
	void run();

private:
	SlotMachine machine;
	FSM fsm;	
	SMWindow window;
	bool isSpinning;
};