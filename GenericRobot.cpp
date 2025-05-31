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

    int tx = x + dx;
    int ty = y + dy;
    shells--;

    if (tx >= 0 && tx < (int)battlefield.size() &&
        ty >= 0 && ty < (int)battlefield[0].size())
    {
        if ((rand() % 100) < 70)
        {
            for (Robot *r : robots)
            {
                if (r->isAlive() && r != this && r->getX() == tx && r->getY() == ty)
                {
                    cout << name << " hit and killed " << r->getName()
                         << " at (" << tx << "," << ty << ")\n";
                    log << name << " hit and killed " << r->getName()
                        << " at (" << tx << "," << ty << ")\n";
                    r->kill(battlefield, log);

                    if (!ability)
                    {
                        int choice = rand() % 3;

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
                    }

                    return;
                }
            }
            cout << name << " hit an empty spot.\n";
            log << name << " hit an empty spot.\n";
        }
        else
        {
            cout << name << " missed at (" << tx << "," << ty << ").\n";
            log << name << " missed at (" << tx << "," << ty << ").\n";
        }
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
                        int choice = rand() % 3;

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
}

void GenericRobot::takeTurn(vector<vector<char>> &battlefield, vector<Robot *> &robots, ofstream &log)
{
    think(log);

    if (ability && ability->isScoutBot())
    {
        ability->activate(this, battlefield, log);
        enableScoutVision(true);
    }

    if (ability && ability->isThirtyShotBot())
    {
        ability->activate(this, battlefield, log);
    }

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

    if (ability && ability->isThirtyShotBot() && shells <= 0)
    {
        std::cout << name << "'s ThirtyShotBot ability expired (shells depleted).\n";
        log << name << "'s ThirtyShotBot ability expired (shells depleted).\n";
        delete ability;
        ability = nullptr;
    }

    enableScoutVision(false);
}

GenericRobot::~GenericRobot()
{
    delete ability;
}
