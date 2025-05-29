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
                        std::vector<Robot*>& robots, std::ofstream& log) {
    if (shells <= 0) {
        std::cout << name << " has no shells and self-destructs!\n";
        kill(battlefield, log);
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
                    r->kill(battlefield, log);
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

void GenericRobot::move(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots, std::ofstream& log) {
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
                    r->kill(battlefield, log);
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

void GenericRobot::takeTurn(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots, std::ofstream& log) {
    think();
    static const int dx[] = {0, -1, 0, 1, 0, -1, 1, -1, 1};
    static const int dy[] = {0, -1, -1, -1, 1, 0, 0, 1, 1};
    int dir = rand() % 9;
    if (look(dx[dir], dy[dir], battlefield) && shells > 0) {
        fire(dx[dir], dy[dir], battlefield, robots, log);
    } else {
        move(battlefield, robots, log);
    }
}
