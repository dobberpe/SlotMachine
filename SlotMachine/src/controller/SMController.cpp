#include "SMController.h"
#include "../utils/Logger.h"

SMController::SMController() : machine(WHEELS), window(WINDOW_SIZE, WHEELS), isSpinning(false) {}

void SMController::run() {
	while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (window.buttonPressed()) {
                    fsm.buttonPressed(machine);
                }
            }
        }

        fsm.update(machine);
        if (fsm.active() != isSpinning) {
            isSpinning = !isSpinning;
            window.updateButton(!isSpinning);
        }
        window.updateWheels(machine.getPositions());
        window.draw();
	}
}
