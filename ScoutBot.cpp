#include "ScoutBot.h"
#include <iostream>
#include "GenericRobot.h"

using namespace std;

void ScoutBot::activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> &robots)
{
    if (!hasUses())
        robot->checkAndResetIfNoUpgrades();
    return;

    cout << robot->getName() << " uses ScoutBot ability! Scans entire battlefield:\n";
    log << robot->getName() << " uses ScoutBot ability! Scans entire battlefield:\n";

    for (int r = 0; r < battlefield.size(); ++r)
    {
        for (int c = 0; c < battlefield[0].size(); ++c)
        {
            char content = battlefield[r][c];
            cout << " (" << r << "," << c << "): " << content << " ";
            log << " (" << r << "," << c << "): " << content << " ";
        }
        cout << "\n";
        log << "\n";
    }

    decrementUse();
}
