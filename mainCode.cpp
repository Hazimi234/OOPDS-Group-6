#include "GenericRobot.h"
#include "HideBot.h"
#include <fstream>

int main() {
    ifstream file("robot_simulation.txt");
    if (!file) {
        cout << "Error: Cannot open file." << endl;
        return 1;
    }

    int rows, cols;
    file >> rows >> cols;
    vector<vector<char>> battlefield(rows, vector<char>(cols, '-'));

    int robotCount;
    file >> robotCount;

    vector<Robot*> robots;
    for (int i = 0; i < robotCount; ++i) {
        string type, name;
        int x, y;
        file >> type >> name >> x >> y;

        Robot* robot = nullptr;
        if (type == "GenericRobot") {
            robot = new GenericRobot(name, x, y);
        } else if (type == "HideBot") {
            robot = new HideBot(name, x, y);
        }

        if (robot) {
            robots.push_back(robot);
            battlefield[x][y] = name[0];
        }
    }

    for (Robot* robot : robots) {
        robot->performTurn(robots);
        Robot* newRobot = robot->checkForUpgrade();
        if (newRobot != robot) {
            delete robot;
            robot = newRobot;
        }
        robot->displayStatus();
    }

    for (Robot* robot : robots) delete robot;
    return 0;
}
