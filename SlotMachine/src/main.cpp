//#include <iostream>
#include "controller/SMController.h"
#include "utils/Logger.h"

int main() {
    try {
        SMController controller;
        controller.run();
    } catch (std::exception& e) {
        // ���������� catch ����
        Logger::getInstance() << Logger::CONTROLLER << Logger::ERROR << e.what() << '\n';
        //std::cerr << e.what() << '\n';
    }

    return 0;
}
