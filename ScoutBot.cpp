#include "ScoutBot.h"
#include <iostream>
#include "GenericRobot.h"

void ScoutBot::activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& robots) {
    if (!hasUses()) 
    robot->checkAndResetIfNoUpgrades();
    return;

    std::cout << robot->getName() << " uses ScoutBot ability! Scans entire battlefield:\n";
    log << robot->getName() << " uses ScoutBot ability! Scans entire battlefield:\n";


    for (int r = 0; r < battlefield.size(); ++r) {
        for (int c = 0; c < battlefield[0].size(); ++c) {
            char content = battlefield[r][c];
            std::cout << " (" << r << "," << c << "): " << content << " ";
            log << " (" << r << "," << c << "): " << content << " ";
        }
        std::cout << "\n"; 
        log << "\n"; 
    }

    decrementUse();
}


