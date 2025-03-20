#pragma once

#include "fsm/FSM.h"
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
	static constexpr int WHEELS = 3;
	static constexpr sf::Vector2u WINDOW_SIZE{ 1200, 1000 };
};