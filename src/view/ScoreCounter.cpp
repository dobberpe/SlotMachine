#include "ScoreCounter.h"
#include "../utils/Logger.h"

#include <cmath>

ScoreCounter::ScoreCounter(sf::Vector2f position) :
    background(backgroundTexture), score(0) {

    for (size_t i = 0; i < digits.size(); ++i) {
        loadTexture(digits[i], digits_paths[i].data());
    }

    loadTexture(backgroundTexture, BACKGROUND_FILE.data());

    for (int i = 0; i < NUMBER_ORDER; ++i) {
        number.push_back(sf::Sprite(digits[0]));
        number[i].setPosition({ position.x + i * CELL_WIDTH + DIGIT_SHIFT,
            position.y + DIGIT_SHIFT});
        number[i].setScale(SPRITE_SCALE);
    }

    background.setTexture(backgroundTexture, true);
    background.setScale(SPRITE_SCALE);
}

void ScoreCounter::setPosition(sf::Vector2f position) {
    sf::Vector2f offset = position - number[0].getPosition();

    for (int i = 0; i < NUMBER_ORDER; ++i) number[i].move(offset);
}

void ScoreCounter::updateScore(short addable) {

    if (addable) {
        score += addable;
        if (score >= MAX_SCORE) score -= MAX_SCORE;

        short del = pow(10, NUMBER_ORDER - 1);
        for (auto& digit : number) {
            int index = del ? score / del % 10 : score % 10;
            digit.setTexture(digits[index]);
            del /= 10;
        }
    }
}

void ScoreCounter::draw(sf::RenderTarget& target,
    sf::RenderStates states) const {

    for (auto& digit : number) {
        sf::Vector2f pos = digit.getPosition() -
            sf::Vector2f{ DIGIT_SHIFT, DIGIT_SHIFT };

        background.setPosition(pos);
        target.draw(background);
        target.draw(digit);
    }
}

void ScoreCounter::loadTexture(sf::Texture& texture, std::string filename) {
    if (!texture.loadFromFile(filename))
        throw std::runtime_error("Couldn't load texture from " + filename);
}


