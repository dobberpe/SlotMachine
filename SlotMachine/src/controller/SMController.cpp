#include "SMController.h"

#include <iostream>

#define WHEELS 1
#define ACCELERATION_STEPS 150
#define WINDOW_SIZE { 1200, 1000 }

SMController::SMController() : machine(WHEELS, ACCELERATION_STEPS), window(WINDOW_SIZE, WHEELS) {}

void SMController::run() {
    std::cout << "run\n";
	while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (window.buttonPressed()) {
                    fsm.buttonPressed(machine);
                    window.updateButton(!machine.isSpinning());
                }
            }
        }
        std::cout << "preUpdate\n";

        fsm.update(machine);
        window.updateWheels(machine.getPositions(), machine.getShifts());
        window.draw();
	}
}
