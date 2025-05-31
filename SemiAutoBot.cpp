#include "SemiAutoBot.h"
#include "GenericRobot.h"
#include <iostream>
#include <cstdlib>

void SemiAutoBot::activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& /*robots*/) {
    std::cout << robot->getName() << "'s SemiAutoBot is active.\n";
    log << robot->getName() << "'s SemiAutoBot is active.\n";
}
