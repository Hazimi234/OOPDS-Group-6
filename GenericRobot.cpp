/**********|**********|**********|
Program: GenericRobot.cpp
Course: Data Structures and Algorithms
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#include <cstdlib>
#include <fstream>
#include "GenericRobot.h"
#include "ScoutBot.h"
#include "ThirtyShotBot.h"
#include "SemiAutoBot.h"
#include "LongShotBot.h"
#include "TrackBot.h"
#include <algorithm>

using namespace std;

GenericRobot::GenericRobot(string t, string n, string xStr, string yStr)
    : Robot(t, n, xStr, yStr) {}

void GenericRobot::think(ofstream &log)
{
    cout << name << " is thinking...\n";
    log << name << " is thinking...\n";
}

bool GenericRobot::look(int dx, int dy, const vector<vector<char>> &battlefield, ofstream &log)
{
    if (scoutVisionThisTurn)
        return true; // Always return true if ScoutBot active

    int lookX = x + dx;
    int lookY = y + dy;
    if (lookX >= 0 && lookX < (int)battlefield.size() &&
        lookY >= 0 && lookY < (int)battlefield[0].size())
    {
        if (lookX == x && lookY == y)
            return false;
        char target = battlefield[lookX][lookY];
        cout << name << " looks at (" << lookX << "," << lookY << "): " << target << "\n";
        log << name << " looks at (" << lookX << "," << lookY << "): " << target << "\n";
        return target != '-' && target != name[0];
    }
    else
    {
        cout << name << " looks out of bounds at (" << lookX << "," << lookY << ")\n";
        log << name << " looks out of bounds at (" << lookX << "," << lookY << ")\n";
    }
    return false;
}

void GenericRobot::fire(int dx, int dy, vector<vector<char>> &battlefield,
                        vector<Robot *> &robots, ofstream &log)
{
    if (shells <= 0)
    {
        cout << name << " has no shells and self-destructs!\n";
        log << name << " has no shells and self-destructs!\n";
        kill(battlefield, log);
        return;
    }

    shells--; // consume shell

    // Expire ThirtyShotBot, SemiAutoBot, or LongShotBot if shells run out
    if (ability && shells <= 0 &&
        (ability->isThirtyShotBot() || ability->isSemiAutoBot() || ability->isLongShotBot()))
    {
        cout << name << "'s ability expired (shells depleted).\n";
        log << name << "'s ability expired (shells depleted).\n";
        delete ability;
        ability = nullptr;
        shells = 10; // reset to generic robot
    }

    int tx = x + dx;
    int ty = y + dy;

    if (tx < 0 || tx >= (int)battlefield.size() || ty < 0 || ty >= (int)battlefield[0].size())
        return; // out of bounds

    int hits = 0;

    // SemiAutoBot fires 3 shots with 70% hit chance
    if (ability && ability->isSemiAutoBot())
    {
        for (int i = 0; i < 3; ++i)
        {
            if ((rand() % 100) < 70)
                ++hits;
        }
    }
    else
    {
        if ((rand() % 100) < 70)
            hits = 1;
    }

    for (Robot *r : robots)
    {
        if (r->isAlive() && r != this && r->getX() == tx && r->getY() == ty)
        {
            if (hits > 0)
            {
                cout << name << " hit and killed " << r->getName();
                log << name << " hit and killed " << r->getName();
                if (ability && ability->isSemiAutoBot())
                {
                    cout << " with SemiAutoBot (" << hits << "/3 hits)";
                    log << " with SemiAutoBot (" << hits << "/3 hits)";
                }
                cout << " at (" << tx << "," << ty << ")\n";
                log << " at (" << tx << "," << ty << ")\n";

                r->kill(battlefield, log);

                if (!ability)
                {
                    int choice = rand() % 4;
                    if (choice == 0)
                    {
                        ability = new ThirtyShotBot();
                        cout << name << " gained the ThirtyShotBot ability!\n";
                        log << name << " gained the ThirtyShotBot ability!\n";
                    }
                    else if (choice == 1)
                    {
                        ability = new ScoutBot();
                        cout << name << " gained the ScoutBot ability!\n";
                        log << name << " gained the ScoutBot ability!\n";
                    }
                    else if (choice == 2)
                    {
                        ability = new SemiAutoBot();
                        cout << name << " gained the SemiAutoBot ability!\n";
                        log << name << " gained the SemiAutoBot ability!\n";
                    }
                    else if (choice == 3)
                    {
                        ability = new LongShotBot();
                        cout << name << " gained the LongShotBot ability!\n";
                        log << name << " gained the LongShotBot ability!\n";
                    }
                    else if (choice == 4)
                    {
                        ability = new TrackBot();
                        cout << name << " gained the TrackBot ability!\n";
                        log << name << " gained the TrackBot ability!\n";
                    }
                }
            }
            else
            {
                cout << name << " missed all shots at (" << tx << "," << ty << ").\n";
                log << name << " missed all shots at (" << tx << "," << ty << ").\n";
            }

            return;
        }
    }

    // No robot hit
    if (hits > 0)
    {
        if (ability && ability->isSemiAutoBot())
        {
            cout << name << " hit empty space with " << hits << " SemiAutoBot shots at (" << tx << "," << ty << ").\n";
            log << name << " hit empty space with " << hits << " SemiAutoBot shots at (" << tx << "," << ty << ").\n";
        }
        else
        {
            cout << name << " hit an empty spot.\n";
            log << name << " hit an empty spot.\n";
        }
    }
    else
    {
        cout << name << " missed at (" << tx << "," << ty << ").\n";
        log << name << " missed at (" << tx << "," << ty << ").\n";
    }
}

void GenericRobot::move(vector<vector<char>> &battlefield, vector<Robot *> &robots, ofstream &log)
{
    static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dir = rand() % 8;
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (nx >= 0 && nx < (int)battlefield.size() &&
        ny >= 0 && ny < (int)battlefield[0].size())
    {
        char target = battlefield[nx][ny];
        if (target != '-' && target != name[0])
        {
            for (Robot *r : robots)
            {
                if (r->isAlive() && r->getX() == nx && r->getY() == ny)
                {
                    cout << name << " moves into (" << nx << "," << ny << ") and destroys " << r->getName() << "!\n";
                    log << name << " moves into (" << nx << "," << ny << ") and destroys " << r->getName() << "!\n";
                    r->kill(battlefield, log);

                    // This gives the ability too
                    // Grant ability if none
                    if (!ability)
                    {
                        int choice = rand() % 5;

                        if (choice == 0)
                        {
                            ability = new ThirtyShotBot();
                            cout << name << " gained the ThirtyShotBot ability!\n";
                            log << name << " gained the ThirtyShotBot ability!\n";
                        }
                        else if (choice == 1)
                        {
                            ability = new ScoutBot();
                            cout << name << " gained the ScoutBot ability!\n";
                            log << name << " gained the ScoutBot ability!\n";
                        }
                        else if (choice == 2)
                        {
                            ability = new SemiAutoBot();
                            cout << name << " gained the SemiAutoBot ability!\n";
                            log << name << " gained the SemiAutoBot ability!\n";
                        }
                        else if (choice == 3)
                        {
                            ability = new LongShotBot();
                            cout << name << " gained the LongShotBot ability!\n";
                            log << name << " gained the LongShotBot ability!\n";
                        }
                        else if (choice == 4)
                        {
                            ability = new TrackBot();
                            cout << name << " gained the TrackBot ability!\n";
                            log << name << " gained the TrackBot ability!\n";
                        }
                    }

                    break;
                }
            }
        }

        if (target == '-' || (target != '-' && target != name[0]))
        {
            battlefield[x][y] = '-';
            x = nx;
            y = ny;
            battlefield[x][y] = name[0];
            cout << name << " moves to (" << x << "," << y << ")\n";
            log << name << " moves to (" << x << "," << y << ")\n";
        }
    }
    else
    {
        cout << name << " cannot move to (" << nx << "," << ny << ")\n";
        log << name << " cannot move to (" << nx << "," << ny << ")\n";
    }
}

void GenericRobot::takeTurn(vector<vector<char>> &battlefield, vector<Robot *> &robots, ofstream &log)
{
    think(log);

    if (ability && ability->isThirtyShotBot())
    {
        ability->activate(this, battlefield, log, robots);
    }

    // ScoutBot ability handling
    if (ability && ability->isScoutBot())
    {
        ability->activate(this, battlefield, log, robots);
        enableScoutVision(true);

        bool scoutFired = false;
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                int ni = x + i;
                int nj = y + j;
                if (ni >= 0 && ni < battlefield.size() && nj >= 0 && nj < battlefield[0].size())
                {
                    char target = battlefield[ni][nj];
                    if (target != '-' && target != name[0])
                    {
                        fire(i, j, battlefield, robots, log); // fire only if close
                        scoutFired = true;
                        break;
                    }
                }
            }
            if (scoutFired)
                break;
        }

        if (!scoutFired)
        {
            move(battlefield, robots, log);
        }

        enableScoutVision(false);
    }
    else if (ability && ability->isTrackBot())
    {
        ability->activate(this, battlefield, log, robots);

        // Get tracked enemy robot pointer
        Robot *trackedEnemy = getTrackedEnemy(); // You need a getter like this in your GenericRobot

        if (trackedEnemy)
        {
            // Calculate relative position to tracked enemy
            int dx = trackedEnemy->getX() - x;
            int dy = trackedEnemy->getY() - y;

            // Check if tracked enemy is within firing range (e.g., adjacent or close enough)
            if (abs(dx) <= 1 && abs(dy) <= 1 && shells > 0)
            {
                std::cout << name << " fires at tracked enemy " << trackedEnemy->getName() << "\n";
                log << name << " fires at tracked enemy " << trackedEnemy->getName() << "\n";
                fire(dx, dy, battlefield, robots, log);
            }
        }
        else
        {
            move(battlefield, robots, log); // No tracked enemy, fallback
        }
    }
    // random movement or firing
    else
    {
        static const int dx[] = {0, -1, 0, 1, 0, -1, 1, -1, 1};
        static const int dy[] = {0, -1, -1, -1, 1, 0, 0, 1, 1};
        int dir = rand() % 9;

        if (look(dx[dir], dy[dir], battlefield, log) && shells > 0)
        {
            fire(dx[dir], dy[dir], battlefield, robots, log);
        }
        else
        {
            move(battlefield, robots, log);
        }
    }

    enableScoutVision(false);
}

bool GenericRobot::isEnemyTracked(Robot *enemyRobot) const
{
    return std::find(trackedEnemies.begin(), trackedEnemies.end(), enemyRobot) != trackedEnemies.end();
}

GenericRobot::~GenericRobot()
{
    delete ability;
}
