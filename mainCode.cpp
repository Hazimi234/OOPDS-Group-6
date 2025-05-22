#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Robot
{
public:
    virtual void takeTurn() = 0; 
    virtual string getName() const = 0;
    virtual char getSymbol() const = 0;
    virtual ~Robot() {}
};

class MovingRobot
{
public:
    virtual void move(int dx, int dy) = 0;
    virtual ~MovingRobot() {}
};

class Battlefield
{
private:
    vector<vector<Robot *>> grid;
public:
    void display();
    bool isOccupied(int x, int y);
    Robot *getRobotAt(int x, int y);
    void moveRobot(Robot *r, int newX, int newY);
};

class RobotInfo
{
private:
    string type;   
    string name;   
    int x, y;      
    bool isRandom; 

public:
    // Constructor
    RobotInfo(string t, string n, string xStr, string yStr)
    {
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
    void setPosition(int row, int col)
    {
        x = row;
        y = col;
        isRandom = false;
    }
};

int main()
{
    ifstream file("robot_simulation.txt");
    if (!file)
    {
        cout << "Error: Cannot open file.\n";
        return 1;
    }

    string line;
    int rows = 0, cols = 0;

    // Read battlefield dimensions
    if (getline(file, line))
    {
        size_t pos = line.find(':');
        if (pos != string::npos)
        {
            istringstream iss(line.substr(pos + 1));
            iss >> rows >> cols;
        }
    }

    // Check if dimensions are valid
    if (rows <= 0 || cols <= 0)
    {
        cerr << "Invalid battlefield size.\n";
        return 1;
    }

    // Initialize battlefield with '-' characters
    vector<vector<char>> matrix(rows, vector<char>(cols, '-'));

    // Read number of robots 
    int robotCount = 0;
    if (getline(file, line))
    {
        istringstream iss(line);
        string label;
        iss >> label >> robotCount;
    }

    // Read robot entries and store them in a vector of RobotInfo pointers
    vector<RobotInfo *> robots;
    for (int i = 0; i < robotCount; ++i)
    {
        if (getline(file, line))
        {
            istringstream iss(line);
            string type, name, xStr, yStr;
            iss >> type >> name >> xStr >> yStr;

            RobotInfo *robot = new RobotInfo(type, name, xStr, yStr);
            robots.push_back(robot);
        }
    }

    // Place robots on the battlefield
    srand(time(0)); 
    for (RobotInfo *r : robots)
    {
        int x = r->getX();
        int y = r->getY();

        // If the robot has a random position, find an empty spot
        if (r->getIsRandom())
        {
            do
            {
                x = rand() % rows;
                y = rand() % cols;
            } while (matrix[x][y] != '-'); // Ensure position is empty

            r->setPosition(x, y); 
        }

        // Place the robot on the battlefield using the first letter of its name
        matrix[r->getX()][r->getY()] = r->getName()[0];
    }

    // Print the battlefield
    for (const auto &row : matrix)
    {
        for (char ch : row)
        {
            cout << ch;
        }
        cout << '\n';
    }

    // Clean up dynamically allocated memory
    for (RobotInfo *r : robots)
    {
        delete r;
    }

    return 0;
}
