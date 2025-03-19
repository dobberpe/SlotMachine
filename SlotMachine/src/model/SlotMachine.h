#pragma once

#include "Wheel.h"

class SlotMachine {

public:
	SlotMachine() = delete;
	SlotMachine(int numOfWheels);
	
	~SlotMachine() = default;
	void start();
	void stop();
	bool spin();
	std::vector<std::vector<double>> getPositions() const;

private:
	double randomDouble(std::mt19937& gen, double min, double max) const;
	
	int numberOfWheels;
	std::vector<Wheel> wheels;
};

