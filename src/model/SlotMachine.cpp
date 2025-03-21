#include "SlotMachine.h"
#include "../utils/Logger.h"

SlotMachine::SlotMachine(int numOfWheels) : numberOfWheels(numOfWheels),
	startedSlowing(std::optional<bool>(false)) {

	std::mt19937 gen(std::random_device{}());

	wheels.reserve(numberOfWheels);

	for (int i = 0; i < numberOfWheels; ++i) {
		wheels.push_back(Wheel(SYMBOLS, gen, 0.0,
						randomDouble(gen, 12.0, 15.0),
						randomDouble(gen, 2.0, 4.0),
						randomDouble(gen, 3.0, 5.0)));
	}

	Logger::getInstance() <<	Logger::MODEL <<
								Logger::INFO <<
								"SlotMachine initialized with " <<
								numberOfWheels << " wheels\n";
}

void SlotMachine::start() {

	startedSlowing = std::optional<bool>(false);

	for (auto& wheel : wheels) {
		wheel.start();
	}

	Logger::getInstance() <<	Logger::MODEL <<
								Logger::INFO <<
								"SlotMachine start\n";
}

void SlotMachine::stop() {

	for (auto& wheel : wheels) {
		wheel.stop();
	}

	Logger::getInstance() <<	Logger::MODEL <<
								Logger::INFO <<
								"SlotMachine stop\n";
}

bool SlotMachine::spin() {

	if (startedSlowing.has_value() && *startedSlowing) {
		startedSlowing = std::nullopt;
	}

	int slowing = 0;
	int stopped = 0;

	for (auto& wheel : wheels) {
		wheel.spin();
		wheel.updateSpeed();
		if (wheel.isSlowing()) ++slowing;
		if (!wheel.isSpinning()) ++stopped;
	}

	if (startedSlowing.has_value() && slowing == numberOfWheels) {
		*startedSlowing = true;
	}

	return stopped == numberOfWheels ||
		(startedSlowing.has_value() && *startedSlowing);
}

short SlotMachine::getScore() const {

	bool inRow = true;
	int symbol = wheels[0].getCentral();

	Logger::getInstance() <<	Logger::MODEL <<
								Logger::DEBUG <<
								"symbol = " << symbol << '\n';

	for (int i = 1; i < numberOfWheels && inRow; ++i) {
		int central = wheels[i].getCentral();

		Logger::getInstance() <<	Logger::MODEL <<
									Logger::DEBUG <<
									"central = " << central << '\n';
		
		if (wheels[i].getCentral() != symbol) inRow = false;
	}

	return inRow ? symbol + 1 : 0;
}

std::vector<std::vector<double>> SlotMachine::getPositions() const {

	std::vector <std::vector<double>> positions;

	for (const auto& wheel : wheels) {
		positions.push_back(wheel.getPosition());
	}

	return positions;
}

double SlotMachine::randomDouble(std::mt19937& gen, double min,
	double max) const {

	std::uniform_real_distribution<double> dist(min, max);

	return dist(gen);
}