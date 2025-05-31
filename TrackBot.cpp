#include "TrackBot.h"
#include "GenericRobot.h"
#include "Robot.h"

void TrackBot::activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& robots) {
    if (!hasUses()) return;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int ni = robot->getX() + i;
            int nj = robot->getY() + j;

            if (ni >= 0 && ni < battlefield.size() && nj >= 0 && nj < battlefield[0].size()) {
                char targetChar = battlefield[ni][nj];
                if (targetChar != '-' && targetChar != robot->getName()[0]) {

                    // Find the Robot* matching the symbol
                    for (Robot* r : robots) {
                        if (r->getName()[0] == targetChar) {
                            std::cout << robot->getName() << " plants a tracker on " << targetChar << " at (" << ni << "," << nj << ")\n";
                            log << robot->getName() << " plants a tracker on " << targetChar << " at (" << ni << "," << nj << ")\n";
                            robot->addTrackedEnemy(r);
                            decrementUse();
                            return;
                        }
                    }
                }
            }
        }
    }
    std::cout << robot->getName() << " tried to use TrackBot but saw no enemies nearby.\n";
    log << robot->getName() << " tried to use TrackBot but saw no enemies nearby.\n";
}
