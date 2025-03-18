#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <random>

class Wheel {
private:
	int wheelSize;
	std::vector<int> symbols;
	int position;
	std::chrono::steady_clock::time_point lastUpdate;
	double wheelSpeed; // оборотов в секунду
	long long timeAccumulator;
public:
	Wheel() = delete;
	Wheel(int sz, std::mt19937 gen, double sp);
	~Wheel() = default;
	std::vector<int> getPosition() const;
	void start();
	void speedUp();
	bool speedDown();
	void stop();
	void spin();
	double getShift() const;
};

