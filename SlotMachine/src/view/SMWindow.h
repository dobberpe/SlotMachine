#pragma once

#include <vector>
#include <memory>

#include "WheelView.h"

class SMWindow {
public:
    SMWindow() = delete;
    
    SMWindow(sf::Vector2u windowSize, int numberOfWheels);
    
    ~SMWindow() = default;
    
    bool isOpen() const;
    
    std::optional<sf::Event> pollEvent();
    
    void close();
    
    bool buttonPressed() const;
    
    void updateButton(bool spin);
    
    void updateWheels(std::vector<std::vector<double>> positions);
    
    void draw();

private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<WheelView>> wheels;
    sf::RectangleShape button;
    sf::Font font;
    sf::Text buttonText;

    static constexpr sf::Vector2f BUTTON_SIZE = { 200, 200 };
    static constexpr sf::Vector2f BUTTON_POS = { 500, 800 };
    static constexpr sf::Vector2f BUTTON_TEXT_POS = { 550, 850 };
    static constexpr std::string_view FONT_FILE = "assets/fonts/arial.ttf";
    static constexpr std::string_view SPIN = "SPIN";
    static constexpr std::string_view STOP = "STOP";
    static constexpr sf::Color SPIN_COLOR = sf::Color::Blue;
    static constexpr sf::Color STOP_COLOR = sf::Color::Red;
    static constexpr unsigned int BUTTON_TEXT_FONT_SIZE = 24;
};

