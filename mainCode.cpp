#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Class to store basic robot information (type, name, position)
class RobotInfo {
private:
    string type;    // Robot type (e.g., "GenericRobot")
    string name;    // Robot name (e.g., "Kidd")
    int x, y;       // Position in the battlefield
    bool isRandom;  // True if position is "random random"

public:
    // Constructor: sets type, name, and determines if position is random
    RobotInfo(string t, string n, string xStr, string yStr) {
        type = t;
        name = n;
        isRandom = (xStr == "random" || yStr == "random");
        x = isRandom ? -1 : stoi(xStr);
        y = isRandom ? -1 : stoi(yStr);
    }

    // Getters
    string getType() const { return type; }
    string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool getIsRandom() const { return isRandom; }

    // Sets the position if it was random
    void setPosition(int row, int col) {
        x = row;
        y = col;
        isRandom = false;
    }
};

int main() {
    ifstream file("robot_simulation.txt");
    if (!file) {
        cout << "Error: Cannot open file.\n";
        return 1;
    }

    string line;
    int rows = 0, cols = 0;

    // Step 1: Read battlefield dimensions (e.g., "M by N : 40 50")
    if (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            istringstream iss(line.substr(pos + 1));
            iss >> rows >> cols;
        }
    }

    // Check if dimensions are valid
    if (rows <= 0 || cols <= 0) {
        cerr << "Invalid battlefield size.\n";
        return 1;
    }

    // Step 2: Initialize battlefield with '-' characters
    vector<vector<char>> matrix(rows, vector<char>(cols, '-'));

    // Step 3: Read number of robots (e.g., "robots: 5")
    int robotCount = 0;
    if (getline(file, line)) {
        istringstream iss(line);
        string label;
        iss >> label >> robotCount;
    }

    // Step 4: Read robot entries and store them in a vector of RobotInfo pointers
    vector<RobotInfo*> robots;
    for (int i = 0; i < robotCount; ++i) {
        if (getline(file, line)) {
            istringstream iss(line);
            string type, name, xStr, yStr;
            iss >> type >> name >> xStr >> yStr;

            RobotInfo* robot = new RobotInfo(type, name, xStr, yStr);
            robots.push_back(robot);
        }
    }

    // Step 5: Place robots on the battlefield
    srand(time(0)); // Seed random number generator once
    for (RobotInfo* r : robots) {
        int x = r->getX();
        int y = r->getY();

        // If the robot has a random position, find an empty spot
        if (r->getIsRandom()) {
            do {
                x = rand() % rows;
                y = rand() % cols;
            } while (matrix[x][y] != '-'); // Ensure position is empty

            r->setPosition(x, y); // Set the chosen position
        }

        // Place the robot on the battlefield using the first letter of its name
        matrix[r->getX()][r->getY()] = r->getName()[0];
    }

    // Step 6: Print the battlefield (no spaces as per your request)
    for (const auto& row : matrix) {
        for (char ch : row) {
            cout << ch;
        }
        cout << '\n';
    }

    // Step 7: Clean up dynamically allocated memory
    for (RobotInfo* r : robots) {
        delete r;
    }

    return 0;
}
