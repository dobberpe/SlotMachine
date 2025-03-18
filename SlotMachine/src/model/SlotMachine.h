#pragma once

#include "Wheel.h"

class SlotMachine {
private:
	int numberOfWheels;
	std::vector<Wheel> wheels;
	const int accelerationSteps;
	int accelerationCounter;
	bool spinning;

public:
	SlotMachine() = delete;
	SlotMachine(int numOfWheels, int accSteps);
	
	~SlotMachine() = default;
	//void start();
	void start();
	bool accelerate();
	bool decelerate();
	void spin();
	std::vector<std::vector<int>> getPositions() const;
	std::vector<double> getShifts() const;
	bool isSpinning() const;
};

