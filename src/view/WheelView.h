#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <utility>

class WheelView : public sf::Drawable {
public:
    WheelView() = delete;

    WheelView(const WheelView&) = delete;

    WheelView& operator=(const WheelView&) = delete;

    WheelView(WheelView&&) = delete;
    
    WheelView& operator=(WheelView&&) = delete;
    
    WheelView(sf::Vector2f position, sf::Vector2f windowSize);
    
    ~WheelView() = default;
    
    void update(std::vector<double> positions);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void loadTexture(sf::Texture& texture, std::string filename);

    sf::View view;
    std::array<sf::Texture, 3> textures;
    std::vector<std::pair<sf::Sprite, sf::Sprite>> icons;
    sf::Texture backgroundTexture;
    mutable sf::Sprite background;
    double x;

    static constexpr int SYMBOLS = 3;
    static constexpr int SYMBOL_SHIFT = 25;
    static constexpr int WIDTH = 250;
    static constexpr int HEIGHT = 750;
    static constexpr std::array<std::string_view, 3> texture_paths{
        "assets/img/seven.png",
        "assets/img/lemon.png",
        "assets/img/cherries.png"
    };
    static constexpr std::string_view BACKGROUND_FILE = "assets/img/back.jpg";
};

