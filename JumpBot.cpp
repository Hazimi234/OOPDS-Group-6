#include "JumpBot.h"
#include "GenericRobot.h"
#include <cstdlib>
#include <ctime>

using namespace std;

JumpBot::JumpBot() : jumpsRemaining(3) {}

void JumpBot::activate(GenericRobot *robot, vector<vector<char>> &battlefield,
                       ostream &log, const vector<Robot *> &robots)
{
    if (jumpsRemaining <= 0 || !robot->isAlive())
    {
        log << robot->getName() << " has no jumps left or is dead.\n";
        cout << robot->getName() << " has no jumps left or is dead.\n";
        robot->checkAndResetIfNoUpgrades();
        return;
    }

    int rows = battlefield.size();
    int cols = battlefield[0].size();

    int newX, newY;
    do
    {
        newX = rand() % rows;
        newY = rand() % cols;
    } while (battlefield[newX][newY] != '-'); // Find an empty cell

    // Clear the old position
    battlefield[robot->getX()][robot->getY()] = '-';

    // Update position
    robot->setPosition(newX, newY);
    battlefield[newX][newY] = robot->getName()[0];
    --jumpsRemaining;

    log << robot->getName() << " jumped to (" << newX << "," << newY << "). "
        << "Jumps remaining: " << jumpsRemaining << "\n";
    cout << robot->getName() << " jumped to (" << newX << "," << newY << "). "
         << "Jumps remaining: " << jumpsRemaining << "\n";
}

bool JumpBot::isJumpBot() const
{
    return true;
}
