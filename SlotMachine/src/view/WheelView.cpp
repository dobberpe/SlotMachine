#include "WheelView.h"
#include "../utils/Logger.h"

#include <exception>

#define SYMBOLS 3
#define SEVEN_FILE "assets/img/seven.png"
#define LEMON_FILE "assets/img/lemon.png"
#define CHERRIES_FILE "assets/img/cherries.png"

#define WIDTH 200
#define HEIGHT 600

WheelView::WheelView(sf::Vector2f position, sf::Vector2f windowSize) : view(sf::FloatRect(position, { WIDTH, HEIGHT })), seven(sevenTexture), lemon(lemonTexture), cherries(cherriesTexture),
	seven2(sevenTexture), lemon2(lemonTexture), cherries2(cherriesTexture) {
    view.setViewport(sf::FloatRect({ position.x / windowSize.x, position.y / windowSize.y }, { WIDTH / windowSize.x, HEIGHT / windowSize.y }));

	loadTexture(sevenTexture, SEVEN_FILE);
	loadTexture(lemonTexture, LEMON_FILE);
	loadTexture(cherriesTexture, CHERRIES_FILE);

    seven.setTexture(sevenTexture, true);
    lemon.setTexture(lemonTexture, true);
    cherries.setTexture(cherriesTexture, true);

    seven2.setTexture(sevenTexture, true);
    lemon2.setTexture(lemonTexture, true);
    cherries2.setTexture(cherriesTexture, true);

    x = position.x;

    Logger::getInstance() << Logger::VIEW << Logger::DEBUG << "x = " << x << '\n';
}

void WheelView::update(std::vector<double> positions) {

	for (int i = 0; i < positions.size(); ++i) {
        sf::Vector2f pos(x, positions[i] * WIDTH);
        sf::Vector2f pos2(x, positions[i] * WIDTH + (HEIGHT * (positions[i] >= SYMBOLS - 1 ? -1 : 1)));

        if (i == 0) {
            seven.setPosition(pos);
            seven2.setPosition(pos2);
        } else if (i == 1) {
            lemon.setPosition(pos);
            lemon2.setPosition(pos2);
        } else if (i == 2) {
            cherries.setPosition(pos);
            cherries2.setPosition(pos2);
        }
	}
}

void WheelView::setView(sf::RenderWindow& window) const {
    window.setView(view);
}

void WheelView::draw(sf::RenderWindow& window) const {
    window.draw(seven);
    window.draw(lemon);
    window.draw(cherries);
    window.draw(seven2);
    window.draw(lemon2);
    window.draw(cherries2);
}

void WheelView::loadTexture(sf::Texture& texture, std::string filename) {
    if (!texture.loadFromFile(filename))
        throw std::runtime_error("Couldn't load texture from " + filename);
}
