#include "Wheel.h"
#include "../utils/Logger.h"

#include <numeric>

Wheel::Wheel(int size, std::mt19937& gen, double speed, double maxSp,
	double accF, double decF) : wheelSize(size), symbols(size), position(0.0),
	wheelSpeed(speed), maxSpeed(maxSp), realMaxSpeed(maxSp), accelFactor(accF),
	decelFactor(decF), startTime(std::chrono::steady_clock::now()),
	spinning(false), slowingDown(false), stopping(false), backwards(false) {

	std::iota(symbols.begin(), symbols.end(), 0);
	std::shuffle(symbols.begin(), symbols.end(), gen);

	Logger::getInstance() <<	Logger::MODEL <<
								Logger::INFO <<
								"Wheel initialized with " << wheelSize <<
								" symbols, speed = " << wheelSpeed <<
								", maxSpeed = " << maxSpeed <<
								", accelFactor = " << accelFactor <<
								", decelFactor = " << decelFactor << "\n";

	Logger::getInstance() <<	Logger::MODEL <<
								Logger::INFO <<
								"Symbols order: ";

	for (const auto& sym : symbols) {
		Logger::getInstance() << sym;
	}

	Logger::getInstance() << '\n';
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
	realMaxSpeed = maxSpeed;
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
		speedUp(elapsed);
	} else if (slowingDown) {
		speedDown(elapsed);
	} else if (stopping) {
		align(elapsed);
	}
}

void Wheel::speedUp(double elapsed) {

	wheelSpeed = maxSpeed * (1 - std::exp(-accelFactor * elapsed));

	if (wheelSpeed >= maxSpeed * 0.99999) {
		slowingDown = true;
		startTime = std::chrono::steady_clock::now();
	}
}

void Wheel::speedDown(double elapsed) {

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
}

void Wheel::align(double elapsed) {

	if (stopped()) {
		wheelSpeed = 0.0;
		spinning = false;
		stopping = false;
	} else {
		wheelSpeed = realMaxSpeed * (1 - std::exp(-accelFactor * elapsed));
	}
}

void Wheel::spin() {

	if (wheelSpeed) {
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration<double>(now - lastUpdate).count();

		position += elapsed * wheelSpeed;

		if (position >= wheelSize) position -= wheelSize;

		lastUpdate = now;
	}
}

bool Wheel::isSpinning() const {
	return spinning;
}

bool Wheel::isSlowing() const {
	return slowingDown || stopping || !spinning;
}

int Wheel::getCentral() const {

	int positionCounter = round(position);	
	int target = wheelSize / 2;
	int i = 0;

	while (positionCounter < target) {
		++positionCounter;
		++i;
	}
	while (positionCounter > target) {
		--positionCounter;
		--i;
	}

	if (i < 0) i = wheelSize + i;
	else if (i >= wheelSize) i %= wheelSize;

	return symbols[i];
}

bool Wheel::stopped() const {

	double fractional = position - std::floor(position);
	constexpr double epsilon = 0.0025;

	return fractional < epsilon || 1.0 - fractional < epsilon;
}