#include "ThirtyShotBot.h"
#include <iostream>

using namespace std;

void ThirtyShotBot::activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/)
{
    if (!used)
    {
        robot->setShells(30);
        used = true;
        cout << robot->getName() << " now has 30 shells from ThirtyShotBot!\n";
        log << robot->getName() << " now has 30 shells from ThirtyShotBot!\n";
    }
}
