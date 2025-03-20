#pragma once

#include "Wheel.h"

#include <optional>

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
	
	const int numberOfWheels;
	std::vector<Wheel> wheels;
	std::optional<bool> startedSlowing;
	static constexpr int SYMBOLS = 3;
};

