#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <random>

class Wheel {
private:
	int wheelSize;
	std::vector<int> symbols;
	double position;
	std::chrono::steady_clock::time_point lastUpdate;
	double wheelSpeed; // оборотов в секунду
	const double maxSpeed;
	double realMaxSpeed;
	double accelFactor; // скорость разгона
	double decelFactor; // скорость торможения
	std::chrono::steady_clock::time_point startTime;
	//long long timeAccumulator;
	bool spinning;
	bool slowingDown;

public:
	Wheel() = delete;
	Wheel(int sz, std::mt19937& gen, double speed, double maxSp, double accF, double decF);
	~Wheel() = default;
	std::vector<double> getPosition() const;
	void start();
	void stop();
	void updateSpeed();
	void spin();
	bool isSpinning() const;
};

