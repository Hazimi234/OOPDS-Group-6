#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Abstract base class Robot
class Robot {
protected:
    string type;
    string name;
    int x, y;
    bool isRandom;
    bool alive;
    int lives;
    int shells;

public:
    Robot(string t, string n, string xStr, string yStr)
        : type(t), name(n), isRandom((xStr == "random" || yStr == "random")),
          x(isRandom ? -1 : stoi(xStr)), y(isRandom ? -1 : stoi(yStr)),
          alive(true), lives(3), shells(10) {}

    virtual ~Robot() {}

    virtual void takeTurn(vector<vector<char>>& battlefield) = 0;
    virtual void think() = 0;
    virtual void move(vector<vector<char>>& battlefield) = 0;
    virtual void look(int dx, int dy, const vector<vector<char>>& battlefield) = 0;
    virtual void fire(int dx, int dy, vector<vector<char>>& battlefield) = 0;

    string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY) { x = newX; y = newY; isRandom = false; }
    bool isRandomPosition() const { return isRandom; }
    bool isAlive() const { return alive; }
};

class MovingRobot {
public:
    virtual void move(vector<vector<char>>& battlefield) = 0;
};

class ShootingRobot {
public:
    virtual void fire(int dx, int dy, vector<vector<char>>& battlefield) = 0;
};

class SeeingRobot {
public:
    virtual void look(int dx, int dy, const vector<vector<char>>& battlefield) = 0;
};

class ThinkingRobot {
public:
    virtual void think() = 0;
};

// Concrete GenericRobot class
class GenericRobot : public Robot, public MovingRobot, public ShootingRobot, public SeeingRobot, public ThinkingRobot {
public:
    GenericRobot(string t, string n, string xStr, string yStr)
        : Robot(t, n, xStr, yStr) {}

    void takeTurn(vector<vector<char>>& battlefield) override {
        think();
        look(0, 0, battlefield);
        if (shells > 0) fire(0, 1, battlefield); // Simplified fire
        move(battlefield);
    }

    void think() override {
        cout << name << " is thinking...\n";
    }

    void look(int dx, int dy, const vector<vector<char>>& battlefield) override {
        cout << name << " looks around (" << x + dx << "," << y + dy << "):\n";
        int lookX = x + dx, lookY = y + dy;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int lx = lookX + i;
                int ly = lookY + j;
                if (lx >= 0 && lx < (int)battlefield.size() && ly >= 0 && ly < (int)battlefield[0].size()) {
                    cout << battlefield[lx][ly];
                } else {
                    cout << ' ';
                }
            }
            cout << '\n';
        }
    }

    void fire(int dx, int dy, vector<vector<char>>& battlefield) override {
        if (dx == 0 && dy == 0) return;
        int targetX = x + dx;
        int targetY = y + dy;
        if (targetX >= 0 && targetX < (int)battlefield.size() &&
            targetY >= 0 && targetY < (int)battlefield[0].size()) {
            if (shells > 0) {
                --shells;
                if ((rand() % 100) < 70) {
                    cout << name << " hits target at (" << targetX << "," << targetY << ")!\n";
                    battlefield[targetX][targetY] = '-';
                } else {
                    cout << name << " misses target at (" << targetX << "," << targetY << ").\n";
                }
            } else {
                cout << name << " has no shells and self-destructs!\n";
                alive = false;
                battlefield[x][y] = '-';
            }
        }
    }

    void move(vector<vector<char>>& battlefield) override {
        static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dir = rand() % 8;
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx >= 0 && nx < (int)battlefield.size() &&
            ny >= 0 && ny < (int)battlefield[0].size() &&
            battlefield[nx][ny] == '-') {
            battlefield[x][y] = '-';
            x = nx;
            y = ny;
            battlefield[x][y] = name[0];
            cout << name << " moves to (" << x << "," << y << ")\n";
        }
    }
};

int main() {
    ifstream file("robot_simulation.txt");
    if (!file) {
        cout << "Error: Cannot open file.\n";
        return 1;
    }

    string line;
    int rows = 0, cols = 0, steps = 0, robotCount = 0;

    // Read battlefield size
    if (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            istringstream iss(line.substr(pos + 1));
            iss >> rows >> cols;
        }
    }

    if (rows <= 0 || cols <= 0) {
        cerr << "Invalid battlefield size.\n";
        return 1;
    }

    // Initialize battlefield
    vector<vector<char>> matrix(rows, vector<char>(cols, '-'));

    // Read simulation steps
    if (getline(file, line)) {
        istringstream iss(line);
        string label;
        iss >> label >> steps;
    }

    // Read number of robots
    if (getline(file, line)) {
        istringstream iss(line);
        string label;
        iss >> label >> robotCount;
    }

    // Read and create robots
    vector<Robot*> robots;
    for (int i = 0; i < robotCount; ++i) {
        if (getline(file, line)) {
            istringstream iss(line);
            string type, name, xStr = "random", yStr = "random";
            iss >> type >> name >> xStr >> yStr;

            Robot* robot = new GenericRobot(type, name, xStr, yStr);
            robots.push_back(robot);
        }
    }

    // Place robots
    srand(time(0));
    for (Robot* r : robots) {
        int x = r->getX(), y = r->getY();
        if (r->isRandomPosition()) {
            do {
                x = rand() % rows;
                y = rand() % cols;
            } while (matrix[x][y] != '-');
            r->setPosition(x, y);
        }
        matrix[r->getX()][r->getY()] = r->getName()[0];
    }

    // Run simulation
    for (int turn = 0; turn < steps; ++turn) {
        cout << "\nTurn " << turn + 1 << ":\n";
        for (Robot* r : robots) {
            if (r->isAlive()) {
                r->takeTurn(matrix);
            }
        }

        // Display battlefield
        cout << "\nBattlefield:\n";
        for (const auto& row : matrix) {
            for (char ch : row) cout << ch;
            cout << '\n';
        }
    }

    // Cleanup
    for (Robot* r : robots) delete r;

    return 0;
}
