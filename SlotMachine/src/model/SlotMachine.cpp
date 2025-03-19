#include "SlotMachine.h"

#include <iostream>

#define SYMBOLS 3

double SlotMachine::randomDouble(std::mt19937& gen, double min, double max) const {
	std::uniform_real_distribution<double> dist(min, max);

	return dist(gen);
}

SlotMachine::SlotMachine(int numOfWheels) : numberOfWheels(numOfWheels) {
	std::random_device rd;
	std::mt19937 gen(rd());

	for (int i = 0; i < numberOfWheels; ++i) {
		wheels.push_back(Wheel(SYMBOLS, gen, 0.0, randomDouble(gen, 12.0, 15.0), randomDouble(gen, 2.0, 4.0), randomDouble(gen, 3.0, 5.0)));
	}
}

void SlotMachine::start() {
	for (auto& wheel : wheels) {
		wheel.start();
	}
}

void SlotMachine::stop() {
	for (auto& wheel : wheels) {
		wheel.stop();
	}
}

bool SlotMachine::spin() {
	int stopped = 0;

	for (auto& wheel : wheels) {
		wheel.spin();
		wheel.updateSpeed();
		if (!wheel.isSpinning()) ++stopped;
	}

	return stopped == numberOfWheels;
}

std::vector<std::vector<double>> SlotMachine::getPositions() const {
	std::vector <std::vector<double>> positions;

	for (const auto& wheel : wheels) {
		positions.push_back(wheel.getPosition());
	}

	return positions;
}


