#pragma once

#include <SFML/Graphics.hpp>
//#include <vector>
//#include <unordered_map>
#include <string>

class WheelView {
private:
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
    void loadTexture(sf::Texture& texture, std::string filename);
    //std::vector<sf::Sprite> symbols;
    //static const std::unordered_map<int, sf::Texture> textures;
    //sf::Sprite getSprite(int i) const;
public:
    WheelView() = delete;
    WheelView(const WheelView&) = delete;
    WheelView& operator=(const WheelView&) = delete;
    WheelView(WheelView&&) = delete;
    WheelView& operator=(WheelView&&) = delete;
    WheelView(sf::Vector2f position, sf::Vector2f windowSize);
    //WheelView(std::vector<int> sym);
    ~WheelView() = default;
    void update(std::vector<double> positions);
    void setView(sf::RenderWindow& window) const;
    void draw(sf::RenderWindow& window) const;
};

