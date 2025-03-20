#pragma once

#include <vector>
#include <chrono>
#include <random>

class Wheel {
public:
	Wheel() = delete;
	
	Wheel(int sz, std::mt19937& gen, double speed, double maxSp, double accF, double decF);
	
	~Wheel() = default;
	
	std::vector<double> getPosition() const;
	
	void start();
	
	void stop();
	
	void updateSpeed();
	
	void speedUp(double elapsed);
	
	void speedDown(double elapsed);
	
	void align(double elapsed);
	
	void spin();
	
	bool isSpinning() const;
	
	bool isSlowing() const;

private:
	bool stopped() const;
	
	const int wheelSize;
	std::vector<int> symbols;
	double position;
	std::chrono::steady_clock::time_point lastUpdate;
	double wheelSpeed;			// оборотов в секунду
	const double maxSpeed;
	double realMaxSpeed;
	const double accelFactor;	// скорость разгона
	const double decelFactor;	// скорость торможения
	std::chrono::steady_clock::time_point startTime;
	bool spinning;
	bool slowingDown;
	bool stopping;
	bool backwards;
};

