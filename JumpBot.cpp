/**********|**********|**********|
Program: JumpBot.cpp
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

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
