#include "HideBot.h"
#include <iostream>

using namespace std;

bool HideBot::tryHide(GenericRobot *robot, ostream &log)
{
    cout << robot->getName() << " used HideBot to avoid being hit! (" << usesRemaining - 1 << " left)\n";
    log << robot->getName() << " used HideBot to avoid being hit! (" << usesRemaining - 1 << " left)\n";

    usesRemaining--;

    if (usesRemaining <= 0)
    {
        cout << robot->getName() << "'s HideBot ability expired and reverted to GenericRobot.\n";
        log << robot->getName() << "'s HideBot ability expired and reverted to GenericRobot.\n";

        delete robot->movingAbility;
        robot->movingAbility = nullptr;
        robot->checkAndResetIfNoUpgrades();
    }

    return true; // dodged the attack
}

void HideBot::activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/)
{
}
