#include "ThirtyShotBot.h"
#include <iostream>

void ThirtyShotBot::activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log) {
    if (!used) {
        robot->setShells(30);
        used = true;
        std::cout << robot->getName() << " now has 30 shells from ThirtyShotBot!\n";
        log << robot->getName() << " now has 30 shells from ThirtyShotBot!\n";
    }
}


