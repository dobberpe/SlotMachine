#include "Wheel.h"

#include <numeric>
#include <iostream>

Wheel::Wheel(int size, std::mt19937& gen, double speed, double maxSp, double accF, double decF) :
	wheelSize(size), symbols(size), position(0.0), wheelSpeed(speed), maxSpeed(maxSp),
	realMaxSpeed(maxSp), accelFactor(accF), decelFactor(decF),
	startTime(std::chrono::steady_clock::now()), spinning(false),
	slowingDown(false)/*, timeAccumulator(0)*/ {
	std::iota(symbols.begin(), symbols.end(), 0);
	std::shuffle(symbols.begin(), symbols.end(), gen);
}

std::vector<double> Wheel::getPosition() const {
	double positionTmp = position;
	std::vector<double> currentPosition(wheelSize);

	for (int i = 0; i < wheelSize; ++i) {
		currentPosition[symbols[i]] = positionTmp++;
		if (positionTmp >= wheelSize) positionTmp -= wheelSize;
	}

	return currentPosition;
}

void Wheel::start() {
	startTime = std::chrono::steady_clock::now();
	lastUpdate = startTime;
	spinning = true;
}

void Wheel::stop() {
	startTime = std::chrono::steady_clock::now();
	slowingDown = true;
	realMaxSpeed = wheelSpeed;
}

void Wheel::updateSpeed() {
	auto now = std::chrono::steady_clock::now();
	double elapsed = std::chrono::duration<double>(now - startTime).count();

	if (spinning && !slowingDown) {
		wheelSpeed += 0.1;
		//wheelSpeed = maxSpeed * (1 - std::exp(-accelFactor * elapsed));

		if (wheelSpeed >= maxSpeed) {
		//if (wheelSpeed >= maxSpeed * 0.999999) {
			slowingDown = true;
			startTime = std::chrono::steady_clock::now();
		}
	} else if (slowingDown) {
		wheelSpeed -= 0.1;
		//wheelSpeed = realMaxSpeed * std::exp(-decelFactor * elapsed);

		if (wheelSpeed <= 0.1) {
			wheelSpeed = 0.0;
			spinning = false;
			slowingDown = false;
		}
	}
	//std::cout << wheelSpeed << "\n";
}

void Wheel::spin() {

	if (wheelSpeed) {

		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();

		position += elapsed / 1000.0 * wheelSpeed;

		if (position >= wheelSize) position -= wheelSize;

		lastUpdate = now;
	}
}

bool Wheel::isSpinning() const {
	return spinning;
}
