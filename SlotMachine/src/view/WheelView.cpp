#include "WheelView.h"

#include <exception>

#include <iostream>

#define SEVEN_FILE "seven.png"
#define LEMON_FILE "lemon.png"
#define CHERRIES_FILE "cherries.png"

#define WIDTH 200
#define HEIGHT 600


void WheelView::loadTexture(sf::Texture& texture, std::string filename) {
	if (!texture.loadFromFile(filename))
		throw std::runtime_error("Couldn't load texture from " + filename);

    std::cout << "Loaded texture: " << filename
        << " | Size: " << texture.getSize().x << "x" << texture.getSize().y
        << " | Pointer: " << &texture << std::endl;
}

WheelView::WheelView(sf::Vector2f position, sf::Vector2f windowSize) : view(sf::FloatRect(position, { WIDTH, HEIGHT })), seven(sevenTexture), lemon(lemonTexture), cherries(cherriesTexture),
	seven2(sevenTexture), lemon2(lemonTexture), cherries2(cherriesTexture) {
	view.setViewport(sf::FloatRect(position, { WIDTH / windowSize.x, HEIGHT / windowSize.y }));

	loadTexture(sevenTexture, SEVEN_FILE);
	loadTexture(lemonTexture, LEMON_FILE);
	loadTexture(cherriesTexture, CHERRIES_FILE);

    seven.setTexture(sevenTexture, true);
    lemon.setTexture(lemonTexture, true);
    cherries.setTexture(cherriesTexture, true);

    seven2.setTexture(sevenTexture, true);
    lemon2.setTexture(lemonTexture, true);
    cherries2.setTexture(cherriesTexture, true);

}

void WheelView::update(std::vector<int> positions, double shiftPart) {
    int shift = round(shiftPart * WIDTH);

    sf::Vector2f sevenPos(0, 0);
    sf::Vector2f lemonPos(0, 0);
    sf::Vector2f cherriesPos(0, 0);

    sf::Vector2f seven2Pos(0, 0);
    sf::Vector2f lemon2Pos(0, 0);
    sf::Vector2f cherries2Pos(0, 0);

	for (int i = 0; i < positions.size(); ++i) {
        if (positions[i] == 0) {
            sevenPos.y = 200 * i - shift;
            seven2Pos.y = 200 * i - shift;
            seven2Pos.y += HEIGHT * (shift < 0 ? -1 : 1);
        } else if (positions[i] == 1) {
            lemonPos.y = 200 * i - shift;
            lemon2Pos.y = 200 * i - shift;
            lemon2Pos.y += shift < 0 ? -600 : 600;
        } else if (positions[i] == 2) {
            cherriesPos.y = 200 * i - shift;
            cherries2Pos.y = 200 * i - shift;
            cherries2Pos.y += shift < 0 ? -600 : 600;
        }
	}

    seven.setPosition(sevenPos);
    lemon.setPosition(lemonPos);
    cherries.setPosition(cherriesPos);

    seven2.setPosition(seven2Pos);
    lemon2.setPosition(lemon2Pos);
    cherries2.setPosition(cherries2Pos);
}

void WheelView::setView(sf::RenderWindow& window) const {
    window.setView(view);
}

void WheelView::draw(sf::RenderWindow& window) const {
    std::cout << "draw\n";
    window.draw(seven);
    std::cout << "draw 2\n";
    window.draw(lemon);
    window.draw(cherries);
    window.draw(seven2);
    window.draw(lemon2);
    window.draw(cherries2);
}
