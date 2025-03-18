#pragma once

#include <vector>
#include <optional>
#include <memory>

#include "WheelView.h"

class SMWindow {
private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<WheelView>> wheels;
    sf::RectangleShape button;
    sf::Font font;
    sf::Text buttonText;
public:
    SMWindow() = delete;
    SMWindow(sf::Vector2u windowSize, int numberOfWheels);
    ~SMWindow() = default;
    bool isOpen() const;
    std::optional<sf::Event> pollEvent();
    void close();
    bool buttonPressed() const;
    void updateButton(bool spin);
    void updateWheels(std::vector<std::vector<int>> positions, std::vector<double> shifts);
    void draw();
};

