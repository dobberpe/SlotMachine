#include "RoundedRect.h"

RoundedRect::RoundedRect(sf::Vector2f position, sf::Vector2f size, float radius) 
    : rect(sf::Vector2f(size.x - 2 * radius, size.y - 2 * radius)),
    radius(radius) {

    rect.setPosition({ position.x + radius, position.y + radius });

    for (int i = 0; i < 4; ++i) {
        corners[i].setRadius(radius - OUTLINE_THICKNESS);
        corners[i].setOutlineThickness(OUTLINE_THICKNESS);
        corners[i].setOutlineColor(OUTLINE_COLOR);
    }

    corners[0].setPosition({ position.x + OUTLINE_THICKNESS,
        position.y + OUTLINE_THICKNESS });
    corners[1].setPosition({ position.x + size.x - radius * 2 +
        OUTLINE_THICKNESS, position.y + OUTLINE_THICKNESS });
    corners[2].setPosition({ position.x + OUTLINE_THICKNESS, position.y +
        size.y - radius * 2 + OUTLINE_THICKNESS });
    corners[3].setPosition({ position.x + size.x - radius * 2 +
        OUTLINE_THICKNESS, position.y + size.y - radius * 2 + OUTLINE_THICKNESS });

    for (int i = 0; i < 2; ++i) {
        hBars[i].setSize(sf::Vector2f(size.x - 2 * radius, radius));
    }
    hBars[0].setPosition({ position.x + radius, position.y });
    hBars[1].setPosition({ position.x + radius, position.y + size.y - radius });

    for (int i = 0; i < 2; ++i) {
        vBars[i].setSize(sf::Vector2f(radius, size.y - 2 * radius));
    }
    vBars[0].setPosition({ position.x, position.y + radius });
    vBars[1].setPosition({ position.x + size.x - radius, position.y + radius });

    for (int i = 0; i < 4; ++i) {
        cornersOutline[i].setRadius(OUTLINE_THICKNESS);
        cornersOutline[i].setFillColor(OUTLINE_COLOR);
    }

    cornersOutline[0].setPosition({ position.x + radius - OUTLINE_THICKNESS,
        position.y + radius - OUTLINE_THICKNESS });
    cornersOutline[1].setPosition({ position.x + size.x - radius -
        OUTLINE_THICKNESS, position.y + radius - OUTLINE_THICKNESS });
    cornersOutline[2].setPosition({ position.x + radius - OUTLINE_THICKNESS,
        position.y + size.y - radius - OUTLINE_THICKNESS });
    cornersOutline[3].setPosition({ position.x + size.x - radius -
        OUTLINE_THICKNESS, position.y + size.y - radius - OUTLINE_THICKNESS });

    for (int i = 0; i < 4; ++i) {
        hBarsOutline[i].setSize(sf::Vector2f(size.x - 2 * radius,
            OUTLINE_THICKNESS));
        hBarsOutline[i].setFillColor(OUTLINE_COLOR);
    }
    hBarsOutline[0].setPosition({ position.x + radius, position.y });
    hBarsOutline[1].setPosition({ position.x + radius, position.y + radius -
        OUTLINE_THICKNESS });
    hBarsOutline[2].setPosition({ position.x + radius, position.y + size.y -
        radius});
    hBarsOutline[3].setPosition({ position.x + radius, position.y + size.y -
        OUTLINE_THICKNESS });

    for (int i = 0; i < 4; ++i) {
        vBarsOutline[i].setSize(sf::Vector2f(OUTLINE_THICKNESS, size.y - 2 *
            radius));
        vBarsOutline[i].setFillColor(OUTLINE_COLOR);
    }
    vBarsOutline[0].setPosition({ position.x, position.y + radius });
    vBarsOutline[1].setPosition({ position.x + radius - OUTLINE_THICKNESS,
        position.y + radius });
    vBarsOutline[2].setPosition({ position.x + size.x - radius, position.y +
        radius });
    vBarsOutline[3].setPosition({ position.x + size.x - OUTLINE_THICKNESS,
        position.y + radius });
}

void RoundedRect::setPosition(sf::Vector2f position) {

    sf::Vector2f offset = position - rect.getPosition() +
        sf::Vector2f(radius, radius);

    rect.move(offset);
    for (int i = 0; i < 4; ++i) corners[i].move(offset);
    for (int i = 0; i < 2; ++i) hBars[i].move(offset);
    for (int i = 0; i < 2; ++i) vBars[i].move(offset);
}

void RoundedRect::setFillColor(sf::Color color) {

    rect.setFillColor(color);
    for (int i = 0; i < 4; ++i) corners[i].setFillColor(color);
    for (int i = 0; i < 2; ++i) hBars[i].setFillColor(color);
    for (int i = 0; i < 2; ++i) vBars[i].setFillColor(color);
}

void RoundedRect::drawBorders(sf::RenderTarget& target,
    sf::RenderStates states) const {

    for (const auto& hBar : hBars) target.draw(hBar, states);
    for (const auto& vBar : vBars) target.draw(vBar, states);
    for (const auto& hBarOutline : hBarsOutline) {
        target.draw(hBarOutline, states);
    }
    for (const auto& vBarOutline : vBarsOutline) {
        target.draw(vBarOutline, states);
    }
}

void RoundedRect::draw(sf::RenderTarget& target,
    sf::RenderStates states) const {

    target.draw(rect, states);
    for (const auto& corner : corners) target.draw(corner, states);
    for (const auto& hBar : hBars) target.draw(hBar, states);
    for (const auto& vBar : vBars) target.draw(vBar, states);
    for (const auto& cornerOutline : cornersOutline) {
        target.draw(cornerOutline, states);
    }
    for (const auto& hBarOutline : hBarsOutline) {
        target.draw(hBarOutline, states);
    }
    for (const auto& vBarOutline : vBarsOutline) {
        target.draw(vBarOutline, states);
    }

}
