#include "SlotMachine.h"

#define SYMBOLS 3

SlotMachine::SlotMachine(int numOfWheels) : numberOfWheels(numOfWheels) {
	std::random_device rd;
	std::mt19937 gen(rd());

	for (int i = 0; i < numberOfWheels; ++i) {
		wheels.push_back(Wheel(SYMBOLS, gen, 0.0));
	}
}

void SlotMachine::start() {
	for (auto& wheel : wheels) {
		wheel.start();
	}
}

void SlotMachine::accelerate() {
	for (auto& wheel : wheels) {
		wheel.speedUp();
	}
}

bool SlotMachine::decelerate() {
	int stopped = 0;

	for (auto& wheel : wheels) {
		if (wheel.speedDown())
			++stopped;
	}
	
	return stopped == numberOfWheels;
}

std::vector<double> SlotMachine::spin() {
	std::vector<double> elapsed;

	for (auto& wheel : wheels) {
		elapsed.push_back(wheel.spin());
	}
	
	return elapsed;
}

std::vector<std::vector<int>> SlotMachine::getPositions() const {
	std::vector <std::vector<int>> positions;

	for (const auto& wheel : wheels) {
		positions.push_back(wheel.getPosition());
	}

	return positions;
}