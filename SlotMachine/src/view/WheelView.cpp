#include "WheelView.h"
#include "../utils/Logger.h"

#include <exception>

WheelView::WheelView(sf::Vector2f position, sf::Vector2f windowSize) :
    view(sf::FloatRect(position, { WIDTH, HEIGHT })),
    background(backgroundTexture) {

    view.setViewport(sf::FloatRect(
        { position.x / windowSize.x, position.y / windowSize.y },
        { WIDTH / windowSize.x, HEIGHT / windowSize.y })
    );

    for (int i = 0; i < SYMBOLS; ++i) {
        loadTexture(textures[i], texture_paths[i].data());
        icons.push_back({ sf::Sprite(textures[i]), sf::Sprite(textures[i]) });
    }

    loadTexture(backgroundTexture, BACKGROUND_FILE.data());
    background.setTexture(backgroundTexture, true);

    x = position.x;
}

void WheelView::update(std::vector<double> positions) {

	for (int i = 0; i < positions.size(); ++i) {
        sf::Vector2f pos(x + SYMBOL_SHIFT, positions[i] * WIDTH + SYMBOL_SHIFT);
        sf::Vector2f pos2(
            x + SYMBOL_SHIFT, positions[i] * WIDTH + SYMBOL_SHIFT + (HEIGHT *
                (positions[i] >= SYMBOLS - 1 ? -1 : 1)));

        icons[i].first.setPosition(pos);
        icons[i].second.setPosition(pos2);
	}
}

void WheelView::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.setView(view);

    for (auto& icon : icons) {
        sf::Vector2f pos = icon.first.getPosition();

        background.setPosition(pos - sf::Vector2f{SYMBOL_SHIFT, SYMBOL_SHIFT});
        target.draw(background);
        target.draw(icon.first, states);

        pos = icon.second.getPosition();

        background.setPosition(pos - sf::Vector2f{SYMBOL_SHIFT, SYMBOL_SHIFT});
        target.draw(background);
        target.draw(icon.second, states);
    }
}

void WheelView::loadTexture(sf::Texture& texture, std::string filename) {
    if (!texture.loadFromFile(filename))
        throw std::runtime_error("Couldn't load texture from " + filename);
}
