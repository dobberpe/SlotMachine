#include "SMWindow.h"
#include "../utils/Logger.h"

#include <exception>

SMWindow::SMWindow(sf::Vector2u windowSize, int numberOfWheels) :
	window(sf::VideoMode(windowSize), "SLOT MACHINE"),
	combinationFrame(FRAME_POSITION, FRAME_SIZE, FRAME_RADIUS),
	scoreFrame(SCORE_POSITION, SCORE_SIZE, SCORE_FRAME_RADIUS),
	spinButton(spinButtonTexture), stopButton(stopButtonTexture),
	spinButtonText(font), stopButtonText(font), spinButtonPressTimer(0),
	stopButtonPressTimer(0), scoreCounter(SCORE_COUNTER_POS) {

	window.setFramerateLimit(60);

	combinationFrame.setFillColor(FRAME_COLOR);
	scoreFrame.setFillColor(FRAME_COLOR);

	if (!font.openFromFile(FONT_FILE))
		throw std::runtime_error("Error: Couldn't open font from " +
			std::string(FONT_FILE));

	if (!spinButtonTexture.loadFromFile(SPIN_FILE.data()) ||
		!stopButtonTexture.loadFromFile(STOP_FILE.data())) {

		throw std::runtime_error("Error: Couldn't load button texture");
	}

	spinButton.setPosition(SPIN_BUTTON_POS);
	spinButton.setTexture(spinButtonTexture, true);

	stopButton.setPosition(STOP_BUTTON_POS);
	stopButton.setTexture(stopButtonTexture, true);

	spinButtonText.setString(SPIN.data());
	spinButtonText.setCharacterSize(BUTTON_TEXT_FONT_SIZE);
	spinButtonText.setFillColor(TEXT_COLOR);

	stopButtonText.setString(STOP.data());
	stopButtonText.setCharacterSize(BUTTON_TEXT_FONT_SIZE);
	stopButtonText.setFillColor(TEXT_COLOR);

	sf::FloatRect textBounds = spinButtonText.getLocalBounds();
	spinButtonText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
					 textBounds.position.y + textBounds.size.y / 2.f });

	sf::FloatRect spriteBounds = spinButton.getGlobalBounds();
	spinButtonText.setPosition({ spriteBounds.position +
		spriteBounds.size / 2.f });

	textBounds = stopButtonText.getLocalBounds();
	stopButtonText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
					 textBounds.position.y + textBounds.size.y / 2.f });

	spriteBounds = stopButton.getGlobalBounds();
	stopButtonText.setPosition({ spriteBounds.position +
		spriteBounds.size / 2.f });

	for (int i = 0; i < numberOfWheels; ++i) {
		wheels.emplace_back(std::make_unique<WheelView>(
			sf::Vector2f(250.0 * i + 50, 0),
			static_cast<sf::Vector2f>(windowSize))
		);
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

void SMWindow::pressSpinButton() {

	spinButton.setColor(BUTTON_COLOR_PRESSED);
	spinButtonPressTimer = 10;
}

void SMWindow::pressStopButton() {

	stopButton.setColor(BUTTON_COLOR_PRESSED);
	stopButtonPressTimer = 10;
}

void SMWindow::unpressSpinButton() {

	spinButton.setColor(BUTTON_COLOR);
}

void SMWindow::unpressStopButton() {

	stopButton.setColor(BUTTON_COLOR);
}

bool SMWindow::spinButtonPressed() const {

	sf::Vector2f mousePos = window.mapPixelToCoords(
		sf::Mouse::getPosition(window)
	);
	sf::Vector2f buttonCenter = spinButton.getPosition() +
		spinButton.getGlobalBounds().size / 2.f;

	float radius = spinButton.getGlobalBounds().size.x / 2.f;

	return (std::hypot(mousePos.x - buttonCenter.x,
		mousePos.y - buttonCenter.y) <= radius);
}

bool SMWindow::stopButtonPressed() const {

	sf::Vector2f mousePos = window.mapPixelToCoords(
		sf::Mouse::getPosition(window)
	);
	sf::Vector2f buttonCenter = stopButton.getPosition() +
		stopButton.getGlobalBounds().size / 2.f;

	float radius = stopButton.getGlobalBounds().size.x / 2.f;

	return (std::hypot(mousePos.x - buttonCenter.x,
		mousePos.y - buttonCenter.y) <= radius);
}

bool SMWindow::spinButtonInPressedState() {

	return spinButtonPressTimer > 0 ? --spinButtonPressTimer == 0 : false;
}

bool SMWindow::stopButtonInPressedState() {
	return stopButtonPressTimer > 0 ? --stopButtonPressTimer == 0 : false;
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

void SMWindow::updateScore(short score) {
	Logger::getInstance() <<	Logger::VIEW <<
								Logger::DEBUG <<
								"score = " << score << '\n';

	scoreCounter.updateScore(score);
}

void SMWindow::draw() {
	window.clear(sf::Color::White);

	window.draw(combinationFrame);
	window.draw(scoreFrame);
	
	for (const auto& wheel : wheels) {
		window.draw(*wheel);
	}

	window.setView(window.getDefaultView());
	window.draw(scoreCounter);
	combinationFrame.drawBorders(window, sf::RenderStates::Default);
	scoreFrame.drawBorders(window, sf::RenderStates::Default);
	window.draw(spinButton);
	window.draw(stopButton);
	window.draw(spinButtonText);
	window.draw(stopButtonText);
	window.display();
}
