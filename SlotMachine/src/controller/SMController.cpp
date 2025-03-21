#include "SMController.h"
#include "../utils/Logger.h"

SMController::SMController() : machine(WHEELS), window(WINDOW_SIZE, WHEELS),
    isSpinning(false) {}

void SMController::run() {
    window.updateWheels(machine.getPositions());
    window.draw();

	while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>()) {

                if (window.spinButtonPressed()) {
                    fsm.buttonPressed(machine, window, true);
                } else if (window.stopButtonPressed()) {
                    fsm.buttonPressed(machine, window, false);
                }
            }
        }

        fsm.update(machine, window);
	}
}
