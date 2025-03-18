#include "Wheel.h"

#include <numeric>
#include <iostream>

Wheel::Wheel(int size, std::mt19937 gen, double speed) : wheelSize(size), symbols(size), position(0), wheelSpeed(speed), timeAccumulator(0) {
	std::iota(symbols.begin(), symbols.end(), 0);
	std::shuffle(symbols.begin(), symbols.end(), gen);
}

std::vector<int> Wheel::getPosition() const {
	std::vector<int> currentPosition(wheelSize);

	int j = -1;

	for (int i = position; i < wheelSize; ++i) {
		currentPosition[++j] = symbols[i];
	}
	for (int i = 0; i < position; ++i) {
		currentPosition[++j] = symbols[i];
	}

	return currentPosition;
}

void Wheel::start() {
	lastUpdate = std::chrono::steady_clock::now();
}

void Wheel::speedUp() {
	wheelSpeed += 0.1;
}

bool Wheel::speedDown() {
	const double epsilon = 1e-6;
	bool stopped = false;

	if (abs(wheelSpeed - 0.2) > epsilon) {
		wheelSpeed -= 0.1;
	} else {
		double shiftPart = (double)timeAccumulator / 1000.0 * wheelSpeed;
		int shift = round(shiftPart * 200.0);

		if (shift % 200 == 0) {
			wheelSpeed = 0;
			position += shift = 200 ? 1 : 0;
			position %= wheelSize;
			stopped = true;
		} else if (shiftPart <= 0.2 && wheelSpeed > -0.2) {
			wheelSpeed -= 0.1;
			//std::cout << wheelSpeed << '\n';
		}
	}

	return stopped;
}

void Wheel::stop() {
	wheelSpeed = 0;
}

void Wheel::spin() {
	double res = 0;

	if (wheelSpeed) {

		std::cout << wheelSpeed << '\n';

		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();

		timeAccumulator += elapsed;

		long long timeToSpin = 1000.0 / wheelSpeed;
		int turns = int(timeAccumulator / timeToSpin) % wheelSize;

		if (abs(turns) > 0) {
			position = (position + turns) % wheelSize;
			if (position < 0) position += wheelSize;
			timeAccumulator -= timeToSpin * turns;
		}

		lastUpdate = now;

		res = (double)timeAccumulator / timeToSpin;
	}
}

double Wheel::getShift() const {
	return wheelSpeed ? (double)timeAccumulator / 1000.0 * wheelSpeed : 0;
}