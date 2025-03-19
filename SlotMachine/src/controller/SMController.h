#pragma once

//#include "../model/SlotMachine.h"
#include "../model/fsm/FSM.h"
#include "../view/SMWindow.h"

#include <memory>

class SMController {
private:
	SlotMachine machine;
	FSM fsm;	
	SMWindow window;
	bool isSpinning;
public:
	SMController();
	~SMController() = default;
	void run();
};