#include <iostream>
#include "controller/SMController.h"

int main() {
    try {
        SMController controller;
        controller.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
