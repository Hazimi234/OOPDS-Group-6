#include "SemiAutoBot.h"
#include "GenericRobot.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void SemiAutoBot::activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/)
{
    cout << robot->getName() << "'s SemiAutoBot is active.\n";
    log << robot->getName() << "'s SemiAutoBot is active.\n";
}
