#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <utility>

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
    std::array<sf::Texture, 3> textures;
    std::vector<std::pair<sf::Sprite, sf::Sprite>> icons;
    double x;

    static constexpr int SYMBOLS = 3;
    static constexpr int WIDTH = 200;
    static constexpr int HEIGHT = 600;
    static constexpr std::array<std::string_view, 3> texture_paths{ "assets/img/seven.png",
                                                                    "assets/img/lemon.png",
                                                                    "assets/img/cherries.png"};
};

