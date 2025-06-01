#include "TrackBot.h"
#include "GenericRobot.h"
#include "Robot.h"

using namespace std;

void TrackBot::activate(GenericRobot* robot, vector<vector<char>>& battlefield, ostream& log, const vector<Robot*>& robots) {
    if (!hasUses()) 
    robot->checkAndResetIfNoUpgrades();
    return;

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
                            cout << robot->getName() << " plants a tracker on " << targetChar << " at (" << ni << "," << nj << ")\n";
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
    cout << robot->getName() << " tried to use TrackBot but saw no enemies nearby.\n";
    log << robot->getName() << " tried to use TrackBot but saw no enemies nearby.\n";
}
