#include "HideBot.h"
#include <iostream>

bool HideBot::tryHide(GenericRobot* robot, std::ostream& log) {
    std::cout << robot->getName() << " used HideBot to avoid being hit! (" << usesRemaining - 1 << " left)\n";
    log << robot->getName() << " used HideBot to avoid being hit! (" << usesRemaining - 1 << " left)\n";

    usesRemaining--;

    if (usesRemaining <= 0) {
        std::cout << robot->getName() << "'s HideBot ability expired and reverted to GenericRobot.\n";
        log << robot->getName() << "'s HideBot ability expired and reverted to GenericRobot.\n";

        delete robot->ability;
        robot->ability = nullptr;
    }

    return true; // dodged the attack
}


void HideBot::activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& /*robots*/) {
}
