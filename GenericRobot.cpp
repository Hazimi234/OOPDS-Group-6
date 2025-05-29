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


#include "GenericRobot.h"
#include <cstdlib>

GenericRobot::GenericRobot(std::string t, std::string n, std::string xStr, std::string yStr)
    : Robot(t, n, xStr, yStr) {}

void GenericRobot::think() {
    std::cout << name << " is thinking...\n";
}

bool GenericRobot::look(int dx, int dy, const std::vector<std::vector<char>>& battlefield) {
    int lookX = x + dx;
    int lookY = y + dy;
    if (lookX >= 0 && lookX < (int)battlefield.size() &&
        lookY >= 0 && lookY < (int)battlefield[0].size()) {
        if (lookX == x && lookY == y) return false;
        char target = battlefield[lookX][lookY];
        std::cout << name << " looks at (" << lookX << "," << lookY << "): " << target << "\n";
        return target != '-' && target != name[0];
    }
    return false;
}

void GenericRobot::fire(int dx, int dy, std::vector<std::vector<char>>& battlefield,
                        std::vector<Robot*>& robots) {
    if (shells <= 0) {
        std::cout << name << " has no shells and self-destructs!\n";
        kill(battlefield);
        return;
    }

    int tx = x + dx;
    int ty = y + dy;
    shells--;

    if (tx >= 0 && tx < (int)battlefield.size() &&
        ty >= 0 && ty < (int)battlefield[0].size()) {
        if ((rand() % 100) < 70) {
            for (Robot* r : robots) {
                if (r->isAlive() && r != this && r->getX() == tx && r->getY() == ty) {
                    r->kill(battlefield);
                    std::cout << name << " hit and killed " << r->getName()
                              << " at (" << tx << "," << ty << ")\n";
                    return;
                }
            }
            std::cout << name << " hit an empty spot.\n";
        } else {
            std::cout << name << " missed at (" << tx << "," << ty << ").\n";
        }
    }
}

void GenericRobot::move(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots) {
    static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dir = rand() % 8;
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (nx >= 0 && nx < (int)battlefield.size() &&
        ny >= 0 && ny < (int)battlefield[0].size()) {
        char target = battlefield[nx][ny];
        if (target != '-' && target != name[0]) {
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == nx && r->getY() == ny) {
                    std::cout << name << " moves into (" << nx << "," << ny << ") and destroys " << r->getName() << "!\n";
                    r->kill(battlefield);
                    break;
                }
            }
        }

        if (target == '-' || (target != '-' && target != name[0])) {
            battlefield[x][y] = '-';
            x = nx;
            y = ny;
            battlefield[x][y] = name[0];
            std::cout << name << " moves to (" << x << "," << y << ")\n";
        }
    }
}

void GenericRobot::takeTurn(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots) {
    think();
    static const int dx[] = {0, -1, 0, 1, 0, -1, 1, -1, 1};
    static const int dy[] = {0, -1, -1, -1, 1, 0, 0, 1, 1};
    int dir = rand() % 9;
    if (look(dx[dir], dy[dir], battlefield) && shells > 0) {
        fire(dx[dir], dy[dir], battlefield, robots);
    } else {
        move(battlefield, robots);
    }
}
