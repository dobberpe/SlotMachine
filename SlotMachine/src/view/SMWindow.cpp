#include "SMWindow.h"

#include <exception>

#include <iostream>

#define BUTTON_SIZE { 200, 200 }
#define FONT_FILE "assets/fonts/arial.ttf"
#define BUTTON_POS { 500, 800 }
#define SPIN "SPIN"
#define STOP "STOP"
#define SPIN_COLOR sf::Color::Blue
#define STOP_COLOR sf::Color::Red
#define BUTTON_TEXT_POS { 550, 850 }
#define BUTTON_TEXT_FONT_SIZE 24

SMWindow::SMWindow(sf::Vector2u windowSize, int numberOfWheels) :
	window(sf::VideoMode(windowSize), "Cyclic Image Display"),
	button(BUTTON_SIZE), buttonText(font) {
	window.setFramerateLimit(60);

	if (!font.openFromFile(FONT_FILE))
		throw std::runtime_error("Error: Couldn't open font from " + std::string(FONT_FILE));

	button.setPosition(BUTTON_POS);
	button.setFillColor(SPIN_COLOR);

	//buttonText.setFont(font);
	buttonText.setString(SPIN);
	buttonText.setCharacterSize(BUTTON_TEXT_FONT_SIZE);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(BUTTON_TEXT_POS);

	for (int i = 0; i < numberOfWheels; ++i) {
		wheels.emplace_back(std::make_unique<WheelView>(sf::Vector2f(200.0 * i, 0), sf::Vector2f(1200, 1000)));
	}
}

bool SMWindow::isOpen() const {
	return window.isOpen();
}

std::optional<sf::Event> SMWindow::pollEvent() {
	return window.pollEvent();
}

void SMWindow::close() {
	window.close();
}

bool SMWindow::buttonPressed() const {
	return button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

void SMWindow::updateButton(bool spin) {
	//std::cout << (spin ? SPIN : STOP) << '\n';
	button.setFillColor(spin ? SPIN_COLOR : STOP_COLOR);
	buttonText.setString(spin ? SPIN : STOP);
}

void SMWindow::updateWheels(std::vector<std::vector<double>> positions) {
	if (positions.size() != wheels.size()) {
		throw std::runtime_error("Error: View and Model aren't compatible");
	} else {
		for (int i = 0; i < positions.size(); ++i) {
			wheels[i]->update(positions[i]);
		}
	}
}

void SMWindow::draw() {
	window.clear(sf::Color::White);
	
	for (const auto& wheel : wheels) {
		wheel->setView(window);
		wheel->draw(window);
	}

	window.setView(window.getDefaultView());
	window.draw(button);
	window.draw(buttonText);
	window.display();
}
