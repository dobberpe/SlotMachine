#include <SFML/Graphics.hpp>
#include <iostream>
#include "model/SlotMachine.h"

#define ONE sevenPos
#define TWO lemonPos
#define THREE cherriesPos
#define ONE_COPY sevenCopyPos
#define TWO_COPY lemonCopyPos
#define THREE_COPY cherriesCopyPos

void getWheels(SlotMachine& sm, sf::Vector2f& sevenPos, sf::Vector2f& lemonPos, sf::Vector2f& cherriesPos, sf::Vector2f& sevenCopyPos, sf::Vector2f& lemonCopyPos, sf::Vector2f& cherriesCopyPos, int shift) {
    std::vector<std::vector<int>> wheelPositions = sm.getPositions();

    for (const auto& wheelPos : wheelPositions) {
        for (int i = 0; i < wheelPos.size(); ++i) {
            // mapping needed

            if (wheelPos[i] == 0) {
                ONE.y = 200 * i - shift;
                ONE_COPY.y = 200 * i - shift;
                ONE_COPY.y += shift < 0 ? -600 : 600;
            }
            else if (wheelPos[i] == 1) {
                TWO.y = 200 * i - shift;
                TWO_COPY.y = 200 * i - shift;
                TWO_COPY.y += shift < 0 ? -600 : 600;
            }
            else if (wheelPos[i] == 2) {
                THREE.y = 200 * i - shift;
                THREE_COPY.y = 200 * i - shift;
                THREE_COPY.y += shift < 0 ? -600 : 600;
            }
        }
    }
}

void spin(SlotMachine& sm, sf::Vector2f& sevenPos, sf::Vector2f& lemonPos, sf::Vector2f& cherriesPos, sf::Vector2f& sevenCopyPos, sf::Vector2f& lemonCopyPos, sf::Vector2f& cherriesCopyPos) {
    int shift = 0;

    std::vector<double> elapsed = sm.spin();
    shift = round(elapsed[0] * 200.0);

    getWheels(sm, sevenPos, lemonPos, cherriesPos, sevenCopyPos, lemonCopyPos, cherriesCopyPos, shift);
}

void render() {
    sf::Texture sevenTexture, lemonTexture, cherriesTexture;
    if (!sevenTexture.loadFromFile("seven.png") ||
        !lemonTexture.loadFromFile("lemon.png") ||
        !cherriesTexture.loadFromFile("cherries.png")) {
        std::cout << "shit\n";
        return;
    }

    sf::Sprite seven(sevenTexture);
    sf::Sprite lemon(lemonTexture);
    sf::Sprite cherries(cherriesTexture);

    sf::Sprite sevenCopy(sevenTexture);
    sf::Sprite lemonCopy(lemonTexture);
    sf::Sprite cherriesCopy(cherriesTexture);

    sf::Vector2f sevenPos(0, 0);
    sf::Vector2f lemonPos(0, 200);
    sf::Vector2f cherriesPos(0, 400);

    sf::Vector2f sevenCopyPos(0, 600);
    sf::Vector2f lemonCopyPos(0, 800);
    sf::Vector2f cherriesCopyPos(0, 1000);

    sf::RenderWindow window(sf::VideoMode({ 1200, 1000 }), "Cyclic Image Display");
    window.setFramerateLimit(60);

    // Создаём область видимости 200x600 в координатах сцены
    sf::View view(sf::FloatRect({ 0, 0 }, { 200, 600 }));

    // Указываем, что эта область занимает 200x600 пикселей в ЛЕВОМ ВЕРХНЕМ углу окна
    view.setViewport(sf::FloatRect({ 0.f, 0.f }, { 200.f / 1200.f, 600.f / 1000.f }));

    sf::RectangleShape button({ 200, 200 });  // Кнопка размера 200x200
    button.setPosition({ 500, 800 });  // Позиция кнопки внизу по центру
    button.setFillColor(sf::Color::Blue);  // Задний фон кнопки

    // Текст кнопки
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }
    sf::Text buttonText(font);
    buttonText.setString("Spin");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition({ 550, 850 });  // Позиция текста в кнопке

    SlotMachine sm(1);
    bool isSpinning = false;
    int accelerationTime = 150;
    //bool stopping = false;
    //bool forward = true;

    getWheels(sm, sevenPos, lemonPos, cherriesPos, sevenCopyPos, lemonCopyPos, cherriesCopyPos, 0);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    isSpinning = !isSpinning;
                    if (isSpinning) {
                        buttonText.setString("Stop");
                        button.setFillColor(sf::Color::Red);
                        sm.start();
                    }
                    else {
                        buttonText.setString("Spin");
                        button.setFillColor(sf::Color::Blue);
                    }
                }
            }
        }

        if (isSpinning) {
            if (!accelerationTime && sm.decelerate()) {
                isSpinning = !isSpinning;
                buttonText.setString("Spin");
                button.setFillColor(sf::Color::Blue);
            } else {
                spin(sm, sevenPos, lemonPos, cherriesPos, sevenCopyPos, lemonCopyPos, cherriesCopyPos);

                if (accelerationTime) {
                    sm.accelerate();
                    --accelerationTime;
                }
            }
        }

        seven.setPosition(sevenPos);
        lemon.setPosition(lemonPos);
        cherries.setPosition(cherriesPos);

        sevenCopy.setPosition(sevenCopyPos);
        lemonCopy.setPosition(lemonCopyPos);
        cherriesCopy.setPosition(cherriesCopyPos);

        window.clear(sf::Color::White);

        // Применяем ограниченный вид только к спрайтам
        window.setView(view);
        window.draw(seven);
        window.draw(lemon);
        window.draw(cherries);
        window.draw(sevenCopy);
        window.draw(lemonCopy);
        window.draw(cherriesCopy);

        // Возвращаем стандартный вид для кнопки и текста
        window.setView(window.getDefaultView());
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
}

int main() {
    render();
    return 0;
}
