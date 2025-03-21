#pragma once

#include <SFML/Graphics.hpp>

class RoundedRect : public sf::Drawable {
public:
    RoundedRect(sf::Vector2f position, sf::Vector2f size, float radius);

    void setPosition(sf::Vector2f position);

    void setFillColor(sf::Color color);

    void drawBorders(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape rect;
    sf::CircleShape corners[4];
    sf::RectangleShape hBars[2], vBars[2];
    sf::CircleShape cornersOutline[4];
    sf::RectangleShape hBarsOutline[4], vBarsOutline[4];
    float radius;

    static constexpr float OUTLINE_THICKNESS = 3.f;
    static constexpr sf::Color OUTLINE_COLOR = sf::Color(150, 0, 0);
};