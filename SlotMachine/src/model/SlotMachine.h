#pragma once

#include "Wheel.h"

class SlotMachine {
private:
	int numberOfWheels;
	std::vector<Wheel> wheels;

	double randomDouble(std::mt19937& gen, double min, double max) const;

public:
	SlotMachine() = delete;
	SlotMachine(int numOfWheels);
	
	~SlotMachine() = default;
	void start();
	void stop();
	/*bool accelerate();
	bool decelerate();*/
	bool spin();
	std::vector<std::vector<double>> getPositions() const;
};

