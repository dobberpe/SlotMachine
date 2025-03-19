#pragma once

#include <SFML/Graphics.hpp>
//#include <vector>
//#include <unordered_map>
#include <string>

class WheelView {
public:
    WheelView() = delete;

    WheelView(const WheelView&) = delete;

    WheelView& operator=(const WheelView&) = delete;

    WheelView(WheelView&&) = delete;

    
    WheelView& operator=(WheelView&&) = delete;
    
    WheelView(sf::Vector2f position, sf::Vector2f windowSize);
    
    ~WheelView() = default;
    
    void update(std::vector<double> positions);
    
    void setView(sf::RenderWindow& window) const;
    
    void draw(sf::RenderWindow& window) const;

private:
    void loadTexture(sf::Texture& texture, std::string filename);

    sf::View view;
    sf::Texture sevenTexture;
    sf::Texture lemonTexture;
    sf::Texture cherriesTexture;
    sf::Sprite seven;
    sf::Sprite lemon;
    sf::Sprite cherries;
    sf::Sprite seven2;
    sf::Sprite lemon2;
    sf::Sprite cherries2;
    double x;
};

