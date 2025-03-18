//#pragma once
//
//#include <memory>
//
//#include "SlotMachine.h"
//
//enum UserAction {
//    Spin,
//    Stop
//};
//
//class IState {
//public:
//    virtual ~IState() = default;
//    virtual std::unique_ptr<IState> userInput(SlotMachine& machine, UserAction sction) = 0;
//    virtual std::unique_ptr<IState> update(SlotMachine& machine) = 0;
//};
//
