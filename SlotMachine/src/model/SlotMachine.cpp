#include "SlotMachine.h"

#define SYMBOLS 3

SlotMachine::SlotMachine(int numOfWheels, int accSteps) : numberOfWheels(numOfWheels),
	accelerationSteps(accSteps), accelerationCounter(accelerationSteps), spinning(false) {
	std::random_device rd;
	std::mt19937 gen(rd());

	for (int i = 0; i < numberOfWheels; ++i) {
		wheels.push_back(Wheel(SYMBOLS, gen, 0.0));
	}
}

void SlotMachine::start() {
	accelerationCounter = accelerationSteps;
	for (auto& wheel : wheels) {
		wheel.start();
	}
}

bool SlotMachine::accelerate() {
	for (auto& wheel : wheels) {
		wheel.speedUp();
	}
	return --accelerationCounter == 0;
}

bool SlotMachine::decelerate() {
	int stopped = 0;

	for (auto& wheel : wheels) {
		if (wheel.speedDown())
			++stopped;
	}
	
	return stopped == numberOfWheels;
}

void SlotMachine::spin() {
	for (auto& wheel : wheels) {
		wheel.spin();
	}
}

std::vector<std::vector<int>> SlotMachine::getPositions() const {
	std::vector <std::vector<int>> positions;

	for (const auto& wheel : wheels) {
		positions.push_back(wheel.getPosition());
	}

	return positions;
}

std::vector<double> SlotMachine::getShifts() const {
	std::vector<double> shifts;

	for (const auto& wheel : wheels) {
		shifts.push_back(wheel.getShift());
	}

	return shifts;
}

bool SlotMachine::isSpinning() const {
	return spinning;
}
