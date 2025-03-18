#pragma once

#include "Wheel.h"

class SlotMachine {
private:
	int numberOfWheels;
	std::vector<Wheel> wheels;


public:
	SlotMachine() = delete;
	SlotMachine(int numOfWheels=1);
	
	~SlotMachine() = default;
	//void start();
	void start();
	void accelerate();
	bool decelerate();
	std::vector<double> spin();
	std::vector<std::vector<int>> getPositions() const;
};

