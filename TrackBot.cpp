/**********|**********|**********|
Program: TrackBot.cpp
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#include "TrackBot.h"
#include "GenericRobot.h"
#include "Robot.h"

using namespace std;

void TrackBot::activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> &robots)
{
    if (!hasUses())
        return;

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            int ni = robot->getX() + i;
            int nj = robot->getY() + j;

            if (ni >= 0 && ni < battlefield.size() && nj >= 0 && nj < battlefield[0].size())
            {
                char targetChar = battlefield[ni][nj];
                if (targetChar != '-' && targetChar != robot->getName()[0])
                {

                    // Find the Robot* matching the symbol
                    for (Robot *r : robots)
                    {
                        if (r->getName()[0] == targetChar)
                        {
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
