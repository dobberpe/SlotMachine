#include "SMController.h"

#include <iostream>

#define WHEELS 3
//#define ACCELERATION_STEPS 150
#define WINDOW_SIZE { 1200, 1000 }

SMController::SMController() : machine(WHEELS), window(WINDOW_SIZE, WHEELS), isSpinning(false) {}

void SMController::run() {
	while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (window.buttonPressed()) {
                    std::cout << "pressed\n";
                    fsm.buttonPressed(machine);
                    isSpinning = !isSpinning;
                    window.updateButton(!isSpinning);
                }
            }
        }

        fsm.update(machine);
        window.updateWheels(machine.getPositions());
        window.draw();
	}
}
