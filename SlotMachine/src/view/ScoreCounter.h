#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class ScoreCounter : public sf::Drawable {
public:
    ScoreCounter(sf::Vector2f position);

    void setPosition(sf::Vector2f position);

    void updateScore(short addable);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void loadTexture(sf::Texture& texture, std::string filename);

    std::array<sf::Texture, 10> digits;
    std::vector<sf::Sprite> number;
    sf::Texture backgroundTexture;
    mutable sf::Sprite background;
    short score;

    static constexpr int NUMBER_ORDER = 3;
    static constexpr std::array<std::string_view, 10> digits_paths{
        "assets/img/0.png",
        "assets/img/1.png",
        "assets/img/2.png",
        "assets/img/3.png",
        "assets/img/4.png",
        "assets/img/5.png",
        "assets/img/6.png",
        "assets/img/7.png",
        "assets/img/8.png",
        "assets/img/9.png"
    };

    static constexpr std::string_view BACKGROUND_FILE = "assets/img/back.jpg";
    static constexpr short MAX_SCORE = 1000;
    static constexpr sf::Vector2f SPRITE_SCALE = { 0.4f, 0.4f };
    static constexpr int CELL_WIDTH = 100;
    static constexpr int DIGIT_SHIFT = 10;
};