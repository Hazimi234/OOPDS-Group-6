#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Robot.h"
#include "GenericRobot.h"


using namespace std;

int main() {
    ifstream file("robot_simulation.txt");
    if (!file) {
        cout << "Error: Cannot open file.\n";
        return 1;
    }

    
    // for log file
    ofstream log("log_turns.txt");
    if (!log) {
        cout << "Error: Cannot create log file.\n";
        return 1;
    }

    string line;
    int rows = 0, cols = 0, steps = 0, robotCount = 0;

    if (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            istringstream iss(line.substr(pos + 1));
            iss >> rows >> cols;
        }
    }

    vector<vector<char>> matrix(rows, vector<char>(cols, '-'));
    if (getline(file, line)) { istringstream(line) >> line >> steps; }
    if (getline(file, line)) { istringstream(line) >> line >> robotCount; }

    vector<Robot*> robots;
    srand(time(0));
    int deathsThisTurn=0;

    for (int i = 0; i < robotCount; ++i) {
        if (getline(file, line)) {
            istringstream iss(line);
            string type, name, xStr, yStr;
            iss >> type >> name;
            if (!(iss>>xStr)) xStr="random";
            if (!(iss>>yStr)) yStr="random";

            Robot* robot = new GenericRobot(type, name, xStr, yStr);
            robots.push_back(robot);
        }
    }

    for (Robot* r : robots) {
        int x = r->getX(), y = r->getY();
        if (r->isRandomPosition()) {
            do {
                x = rand() % rows;
                y = rand() % cols;
            } while (matrix[x][y] != '-');
            r->setPosition(x, y);
        }
        // Add bounds check before accessing matrix
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            matrix[r->getX()][r->getY()] = r->getName()[0];
        } else {
            cout << "Error: Robot " << r->getName() << " has invalid position (" << x << "," << y << ").\n";
            log << "Error: Robot " << r->getName() << " has invalid position (" << x << "," << y << ").\n";
            r->setPosition(0, 0); // Or handle as needed
            matrix[0][0] = r->getName()[0];
        }
    }

    for (int turn = 0; turn < steps; ++turn) {
        cout << "\nTurn " << turn + 1 << ":\n";
        log << "\nTurn " << turn + 1 << ":\n";

        // Clear battlefield matrix
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                matrix[r][c] = '-';
            }
        }

        // Place alive robots on battlefield
        for (Robot* r : robots) {
            if (r->isAlive()) {
                int x = r->getX();
                int y = r->getY();
                matrix[x][y] = r->getName()[0];
            }
        }

        int deathsThisTurn = 0;
        int activeCount = 0;

        // Each alive robot takes its turn
        for (Robot* r : robots) {
            if (r->isAlive()) {
                r->takeTurn(matrix, robots, log);
                activeCount++;
            }
        }

        // Count deaths this turn that can respawn
        for (Robot* r : robots) {
            if (!r->isAlive() && r->canRespawn()) {
                deathsThisTurn++;
            }
        }

        // Respawn robots if possible and room available
        for (Robot* r : robots) {
            if (!r->isAlive() && r->canRespawn() && activeCount < 5) {
                r->respawn(matrix, rows, cols, log);
                activeCount++;
            }
        }

        cout << "\nBattlefield";
        log << "\nBattlefield";

        // Tens digits
        cout << "    ";
        log << "    ";
        for (int c = 0; c < cols; ++c) {
            cout << " ";
            log << " ";
            if (c >= 10) {
                cout << c / 10;
                log << c / 10;
            } else {
                cout << " ";
                log << " ";
            }
        }
        cout << '\n';
        log << '\n';

        // Units digits
        cout << "    ";
        log << "    ";
        for (int c = 0; c < cols; ++c) {
            cout << " " << c % 10;
            log << " " << c % 10;
        }
        cout << '\n';
        log << '\n';

        // Battlefield rows
        for (int r = 0; r < rows; ++r) {
            cout << setw(3) << r << " ";
            log << setw(3) << r << " ";
            for (int c = 0; c < cols; ++c) {
                cout << " " << matrix[r][c];
                log << " " << matrix[r][c];
            }
            cout << '\n';
            log << '\n';
        }
    }

    log.close();
    // Cleanup and exit after the simulation loop
    for (Robot* r : robots) delete r;
    return 0;
    
}