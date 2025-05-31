#include "ScoutBot.h"
#include <iostream>
#include "GenericRobot.h"

void ScoutBot::activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log) {
    if (!hasUses()) return;

    log << robot->getName() << " uses ScoutBot ability! Scans entire battlefield:\n";

    robot->clearEnemyPositions();

    for (int r = 0; r < battlefield.size(); ++r) {
        for (int c = 0; c < battlefield[0].size(); ++c) {
            char content = battlefield[r][c];
            if (content != '-' && content != robot->getName()[0]) {
                robot->addEnemyPosition(r, c);
            }

            log << " (" << r << "," << c << "): " << content << " ";
        }
        log << "\n"; 
    }

    decrementUse();
}


