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
                r->setPosition(0, 0); // Or handle as needed
                matrix[0][0] = r->getName()[0];
            }
        }

        for (int turn = 0; turn < steps; ++turn) {
            cout << "\nTurn " << turn + 1 << ":\n";
            int deathsThisTurn = 0;
            int activeCount = 0;
            for (Robot* r : robots) {
                if (r->isAlive()) {
                    r->takeTurn(matrix, robots);
                    activeCount++;
                }
            }
            for (Robot* r:robots){
                if (!r->isAlive() && r->canRespawn()) {
                    deathsThisTurn++;
                }
            }
            for (Robot* r:robots){
                if (!r->isAlive() && r->canRespawn() && activeCount<5){
                    r->respawn(matrix, rows, cols);
                    activeCount++;
                }
            }
            

    cout << "\nBattlefield:\n";

    // Tens digits
    cout << "    ";
    for (int c = 0; c < cols; ++c) {
        cout << " ";
        if (c >= 10) cout << c / 10;
        else cout << " ";
    }
    cout << '\n';

    // Units digits
    cout << "    ";
    for (int c = 0; c < cols; ++c) {
        cout << " " << c % 10;
    }
    cout << '\n';

    // Battlefield rows
    for (int r = 0; r < rows; ++r) {
        cout << setw(3) << r << " ";
        for (int c = 0; c < cols; ++c) {
            cout << " " << matrix[r][c];
        }
        cout << '\n';
    }

    }
    // Cleanup and exit after the simulation loop
    for (Robot* r : robots) delete r;
    return 0;
    }