/**********|**********|**********|
Program: mainCode.cpp  
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

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

int reinforcementsSpawned = 0;
const int maxReinforcements = 3;
vector<string> reinforcementNames = {"Link", "Clank", "Smasher"};

bool fileExists(const string& filename) {
    ifstream f(filename);
    return f.good();
}
//generate next log filename
string getNextLogFilename() {
    int index = 1;
    string newName;
    do {
        newName = "log_" + to_string(index++) + ".txt";
    } while (fileExists(newName));
    return newName;
}
//attempt to spawn a reinforcement robot
void trySpawnReinforcement(vector<vector<char>>& battlefield, vector<Robot*>& robots, int rows, int cols, ofstream& log) {
    if (reinforcementsSpawned >= maxReinforcements)
        return;

    // 20% chance to spawn per turn
    if (rand() % 100 < 20) {
        for (int attempt = 0; attempt < 20; ++attempt) {
            int x = rand() % rows;
            int y = rand() % cols;
            if (battlefield[x][y] == '-') {
                string name = reinforcementNames[reinforcementsSpawned];
                GenericRobot* newBot = new GenericRobot("G", name, to_string(x), to_string(y));
                newBot->setPosition(x, y);
                battlefield[x][y] = name[0];
                robots.push_back(newBot);

                cout << ">>> Reinforcement " << name << " spawned at (" << x << "," << y << ")!\n";
                log << ">>> Reinforcement " << name << " spawned at (" << x << "," << y << ")!\n";

                reinforcementsSpawned++;
                break;
            }
        }
    }
}

int main() {
    ifstream file("robot_simulation.txt");
    if (!file) {
        cout << "Error: Cannot open file.\n";
        return 1;
    }
    

    // for log file

    string baseLog = "current_log.txt";

    // If current_log.txt already exists, rename it
    if (fileExists(baseLog)) {
        string newName = getNextLogFilename();
        if (rename(baseLog.c_str(), newName.c_str()) != 0) {
            cerr << "Failed to rename existing log file.\n";
            return 1;
        }
    }

    ofstream log(baseLog);
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
    //initialize robots from input file
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
    //place robots on battlefield
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

        trySpawnReinforcement(matrix, robots, rows, cols, log);

        cout << "\nBattlefield";
        log << "\nBattlefield";

        // Tens digits (the digits on the top row)
        cout<<endl;
        log << endl;
        cout << "    ";
        log << "    ";
        for (int c = 0; c < cols; ++c) {
            if (c < 10)
                cout << "  ", log << "  ";
            else
                cout << setw(2) << (c / 10), log << setw(2) << (c / 10);
        }
        cout << '\n';
        log << '\n';

        // Units digits
        cout << "    ";
        log << "    ";
        for (int c = 0; c < cols; ++c) {
            cout << setw(2) << (c % 10);
            log << setw(2) << (c % 10);
        }
        cout << '\n';
        log << '\n';

        // Dashed line
        cout << "    ";
        log << "    ";
        for (int c = 0; c < cols; ++c) {
            cout << "--";
            log << "--";
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