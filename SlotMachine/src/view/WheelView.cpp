#include "WheelView.h"
#include "../utils/Logger.h"

#include <exception>

WheelView::WheelView(sf::Vector2f position, sf::Vector2f windowSize) : view(sf::FloatRect(position, { WIDTH, HEIGHT })) {
    view.setViewport(sf::FloatRect({ position.x / windowSize.x, position.y / windowSize.y }, { WIDTH / windowSize.x, HEIGHT / windowSize.y }));

    for (int i = 0; i < SYMBOLS; ++i) {
        loadTexture(textures[i], texture_paths[i].data());
        icons.push_back({ sf::Sprite(textures[i]), sf::Sprite(textures[i]) });
    }

    x = position.x;
}

void WheelView::update(std::vector<double> positions) {

	for (int i = 0; i < positions.size(); ++i) {
        sf::Vector2f pos(x, positions[i] * WIDTH);
        sf::Vector2f pos2(x, positions[i] * WIDTH + (HEIGHT * (positions[i] >= SYMBOLS - 1 ? -1 : 1)));

        icons[i].first.setPosition(pos);
        icons[i].second.setPosition(pos2);
	}
}

void WheelView::setView(sf::RenderWindow& window) const {
    window.setView(view);
}

void WheelView::draw(sf::RenderWindow& window) const {
    for (auto& icon : icons) {
        window.draw(icon.first);
        window.draw(icon.second);
    }
}

void WheelView::loadTexture(sf::Texture& texture, std::string filename) {
    if (!texture.loadFromFile(filename))
        throw std::runtime_error("Couldn't load texture from " + filename);
}
