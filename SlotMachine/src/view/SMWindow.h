#pragma once

#include <vector>
#include <memory>

#include "WheelView.h"
#include "RoundedRect.h"
#include "ScoreCounter.h"

class SMWindow {
public:
    SMWindow() = delete;
    
    SMWindow(sf::Vector2u windowSize, int numberOfWheels);
    
    ~SMWindow() = default;
    
    bool isOpen() const;
    
    std::optional<sf::Event> pollEvent();
    
    void close();

    void pressSpinButton();

    void pressStopButton();

    void unpressSpinButton();

    void unpressStopButton();
    
    bool spinButtonPressed() const;

    bool stopButtonPressed() const;

    bool spinButtonInPressedState();

    bool stopButtonInPressedState();
    
    void updateWheels(std::vector<std::vector<double>> positions);

    void updateScore(short score);
    
    void draw();

private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<WheelView>> wheels;
    RoundedRect combinationFrame;
    RoundedRect scoreFrame;
    sf::Texture spinButtonTexture;
    sf::Texture stopButtonTexture;
    sf::Sprite spinButton;
    sf::Sprite stopButton;
    sf::Text spinButtonText;
    sf::Text stopButtonText;
    int spinButtonPressTimer;
    int stopButtonPressTimer;
    ScoreCounter scoreCounter;
    sf::Font font;

    static constexpr sf::Vector2f FRAME_POSITION = { 0, 200 };
    static constexpr sf::Vector2f FRAME_SIZE = { 850, 350 };
    static constexpr float FRAME_RADIUS = 50;
    static constexpr sf::Color FRAME_COLOR = sf::Color(200, 0, 0);

    static constexpr sf::Vector2f SCORE_POSITION = { 825, 25 };
    static constexpr sf::Vector2f SCORE_SIZE = { 350, 150 };
    static constexpr float SCORE_FRAME_RADIUS = 25;
    
    static constexpr sf::Vector2f SPIN_BUTTON_POS = { 900, 250 };
    static constexpr sf::Vector2f STOP_BUTTON_POS = { 900, 500 };
    static constexpr sf::Color BUTTON_COLOR = sf::Color(255, 255, 255);
    static constexpr sf::Color BUTTON_COLOR_PRESSED = sf::Color(150, 150, 150);

    static constexpr unsigned int BUTTON_TEXT_FONT_SIZE = 48;
    static constexpr std::string_view SPIN = "SPIN";
    static constexpr std::string_view STOP = "STOP";
    static constexpr sf::Color TEXT_COLOR = sf::Color(255, 255, 255, 150);

    static constexpr sf::Vector2f SCORE_COUNTER_POS = { 850, 50 };

    static constexpr std::string_view FONT_FILE = "assets/fonts/impact.ttf";
    static constexpr std::string_view SPIN_FILE = "assets/img/blue_button.png";
    static constexpr std::string_view STOP_FILE = "assets/img/red_button.png";
    static constexpr std::string_view ICON_FILE = "assets/img/seven.png";
    
};

