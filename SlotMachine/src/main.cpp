#include "controller/SMController.h"
#include "utils/Logger.h"

int main() {
    try {
        SMController controller;
        controller.run();
    } catch (std::exception& e) {
        Logger::getInstance() << Logger::CONTROLLER << Logger::ERROR << e.what() << '\n';
    }

    return 0;
}
