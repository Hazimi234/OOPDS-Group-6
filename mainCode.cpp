/**********|**********|**********|
Program: mainCode.cpp  
Course: Data Structures and Algorithms
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

bool fileExists(const string& filename) {
    ifstream f(filename);
    return f.good();
}

string getNextLogFilename() {
    int index = 1;
    string newName;
    do {
        newName = "log_" + to_string(index++) + ".txt";
    } while (fileExists(newName));
    return newName;
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
            cout<< " " << (c/10==0? " ": to_string(c/10));
            log<< " " << (c/10==0? " ": to_string(c/10));      
        }
        cout << endl;
        log << endl;

        // Units digits
        cout << "    ";
        log << "    ";
        for (int c = 0; c < cols; ++c) {
            cout << " " << c % 10;
            log << " " << c % 10;
        }
        cout << endl;
        log << endl;
        

        cout<< "    +"<< string(cols*2,'-')<<endl;
        log<< "    +"<< string(cols*2,'-')<<endl;
        // Battlefield rows
        for (int r = 0; r < rows; ++r) {
            cout << setw(3) << r << " |";
            log << setw(3) << r << " |";
            for (int c = 0; c < cols; ++c) {
                cout << " " << matrix[r][c];
                log << " " << matrix[r][c];
            }
            cout <<endl;
            log << endl;
        }
    }

    log.close();
    // Cleanup and exit after the simulation loop
    for (Robot* r : robots) delete r;
    return 0;
    
}