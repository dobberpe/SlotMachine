#include "Wheel.h"
#include "../utils/Logger.h"

#include <numeric>

bool Wheel::stopped() const {
	double fractional = position - std::floor(position);
	constexpr double epsilon = 0.0025;

	return fractional < epsilon || 1.0 - fractional < epsilon;
}

Wheel::Wheel(int size, std::mt19937& gen, double speed, double maxSp, double accF, double decF) :
	wheelSize(size), symbols(size), position(0.0), wheelSpeed(speed), maxSpeed(maxSp),
	realMaxSpeed(maxSp), accelFactor(accF), decelFactor(decF),
	startTime(std::chrono::steady_clock::now()), spinning(false),
	slowingDown(false), stopping(false), backwards(false) {
	std::iota(symbols.begin(), symbols.end(), 0);
	std::shuffle(symbols.begin(), symbols.end(), gen);

	Logger::getInstance() << Logger::MODEL << Logger::INFO << "Wheel initialized with " << wheelSize << " symbols, speed = " << wheelSpeed << ", maxSpeed = " << maxSpeed << ", accelFactor = " << accelFactor << ", decelFactor = " << decelFactor << "\n";
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

	

	if (spinning && !slowingDown && !stopping) {
		wheelSpeed = maxSpeed * (1 - std::exp(-accelFactor * elapsed));

		if (wheelSpeed >= maxSpeed * 0.99999) {
			slowingDown = true;
			startTime = std::chrono::steady_clock::now();
		}
	} else if (slowingDown) {
		wheelSpeed = realMaxSpeed * std::exp(-decelFactor * elapsed);

		if (wheelSpeed <= 0.4 && wheelSpeed > 0.2) {
			double fractional = position - std::floor(position);
			constexpr double threshold = 0.33;

			backwards = fractional < threshold;
		} else if (wheelSpeed < 0.2) {
			realMaxSpeed = wheelSpeed * (backwards ? -1 : 1);
			startTime = std::chrono::steady_clock::now();
			wheelSpeed = 0.0;
			slowingDown = false;
			stopping = true;

		}

	} else if (stopping) {

		if (stopped()) {
			wheelSpeed = 0.0;
			spinning = false;
			stopping = false;
		} else {
			if (backwards) {
				wheelSpeed = realMaxSpeed * (1 - std::exp(-accelFactor * elapsed));
			} else {
				wheelSpeed = realMaxSpeed * std::pow(0.9, elapsed);
			}
		}
	}
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
