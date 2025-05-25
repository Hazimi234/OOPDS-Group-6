#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

// Abstract capability interfaces
class SeeingRobot {
public:
    virtual bool look(int dx, int dy, const vector<vector<char>>& battlefield) = 0;
    virtual ~SeeingRobot() {}
};

class ShootingRobot {
public:
    virtual void shoot(int dx, int dy, vector<vector<char>>& battlefield,
                       map<pair<int, int>, class Robot*>& positionMap) = 0;
    virtual ~ShootingRobot() {}
};

class ThinkingRobot {
public:
    virtual void think() = 0;
    virtual ~ThinkingRobot() {}
};

class MovingRobot {
public:
    virtual void move(vector<vector<char>>& battlefield) = 0;
    virtual ~MovingRobot() {}
};

// Abstract base class Robot
class Robot {
protected:
    string type, name;
    int x, y;
    bool isRandom, alive;
    int lives, shells;

public:
    Robot(string t, string n, string xStr, string yStr)
        : type(t), name(n), isRandom((xStr == "random" || yStr == "random")),
          x(isRandom ? -1 : stoi(xStr)), y(isRandom ? -1 : stoi(yStr)),
          alive(true), lives(3), shells(10) {}

    virtual ~Robot() {}
    virtual void takeTurn(vector<vector<char>>& battlefield,
                          map<pair<int, int>, Robot*>& positionMap) = 0;

    void markDead(vector<vector<char>>& battlefield) {
        alive = false;
        battlefield[x][y] = '-';
        cout << name << " has been destroyed!\n";
    }
    // virtual void takeTurn(vector<vector<char>>& battlefield, vector<Robot*>& robots) = 0;
    // virtual void think() = 0;
    // virtual bool look(int dx, int dy, const vector<vector<char>>& battlefield) = 0;
    // virtual void fire(int dx, int dy, vector<vector<char>>& battlefield) = 0;
    // virtual void move(vector<vector<char>>& battlefield, vector<Robot*>& robots) = 0;


    string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY) { x = newX; y = newY; isRandom = false; }
    bool isRandomPosition() const { return isRandom; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }

};

// GenericRobot implements all capabilities
class GenericRobot : public Robot, public SeeingRobot, public ShootingRobot, public ThinkingRobot, public MovingRobot {
public:
    GenericRobot(string t, string n, string xStr, string yStr)
        : Robot(t, n, xStr, yStr) {}

    void think() override {
        cout << name << " is thinking...\n";
    }

    bool look(int dx, int dy, const vector<vector<char>>& battlefield) override {
        int lookX = x + dx;
        int lookY = y + dy;
        if (lookX >= 0 && lookX < (int)battlefield.size() &&
            lookY >= 0 && lookY < (int)battlefield[0].size()) {
            char target = battlefield[lookX][lookY];
            cout << name << " looks at (" << lookX << "," << lookY << "): " << target << "\n";
            return target != '-' && target != name[0]; // Enemy spotted
        }
        return false;
    }

    void shoot(int dx, int dy, vector<vector<char>>& battlefield,
               map<pair<int, int>, Robot*>& positionMap) override {
        if (shells <= 0) {
            cout << name << " has no shells and self-destructs!\n";
            markDead(battlefield);
            return;
        }

        int tx = x + dx, ty = y + dy;
        shells--;

        if (tx >= 0 && tx < (int)battlefield.size() &&
            ty >= 0 && ty < (int)battlefield[0].size()) {
            if ((rand() % 100)<100) {
                pair<int, int> pos = {tx, ty};
                if (positionMap.count(pos)) {
                    Robot* victim = positionMap[pos];
                    if (victim != this) {
                        victim->markDead(battlefield);
                        positionMap.erase(pos);
                        cout << name << " hit and killed " << victim->getName()
                             << " at (" << tx << "," << ty << ")\n";
                    } else {
                        cout << name << " tried to shoot itself. Ignored.\n";
                    }
                } else {
                    cout << name << " hit an empty spot.\n";
                }
            } else {
                cout << name << " missed at (" << tx << "," << ty << ").\n";
            }
        }
    }

    // void move(vector<vector<char>>& battlefield) override {
    //     static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    //     static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    //     int dir = rand() % 8;
    //     int nx = x + dx[dir], ny = y + dy[dir];
    //     if (nx >= 0 && nx < (int)battlefield.size() &&
    //         ny >= 0 && ny < (int)battlefield[0].size() &&
    //         battlefield[nx][ny] == '-') {
    void move(vector<vector<char>>& battlefield, vector<Robot*>& robots) override {
    static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dir = rand() % 8;
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (nx >= 0 && nx < (int)battlefield.size() &&
        ny >= 0 && ny < (int)battlefield[0].size()) {
        
        char target = battlefield[nx][ny];
        
        // If not empty and not same robot
        if (target != '-' && target != name[0]) {
            // Eliminate any robot at the target position
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == nx && r->getY() == ny) {
                    r->kill();
                    cout << name << " moves into (" << nx << "," << ny << ") and destroys " << r->getName() << "!\n";
                    break;
                }
            }
        }

        if (target == '-' || target != name[0]) {
            battlefield[x][y] = '-';
            x = nx;
            y = ny;
            battlefield[x][y] = name[0];
            cout << name << " moves to (" << x << "," << y << ")\n";
        }
    }
}

    // void takeTurn(vector<vector<char>>& battlefield,
    //               map<pair<int, int>, Robot*>& positionMap) override {

    void takeTurn(vector<vector<char>>& battlefield, vector<Robot*>& robots) override {
        think();
        static const int dx[] = {0, -1, 0, 1, 0, -1, 1, -1, 1};
        static const int dy[] = {0, -1, -1, -1, 1, 0, 0, 1, 1};
        int dir = rand() % 9;
        if (look(dx[dir], dy[dir], battlefield) && shells > 0) {
            shoot(dx[dir], dy[dir], battlefield, positionMap);
        } else {
            move(battlefield, robots);
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
    map<pair<int, int>, Robot*> positionMap;
    srand(time(0));

    for (int i = 0; i < robotCount; ++i) {
        if (getline(file, line)) {
            istringstream iss(line);
            string type, name, xStr = "random", yStr = "random";
            iss >> type >> name >> xStr >> yStr;

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
            positionMap[{r->getX(), r->getY()}] = r;
        } else {
            cout << "Error: Robot " << r->getName() << " has invalid position (" << x << "," << y << ").\n";
            r->setPosition(0, 0); // Or handle as needed
            matrix[0][0] = r->getName()[0];
            positionMap[{0, 0}] = r;
        }
    }

    for (int turn = 0; turn < steps; ++turn) {
        cout << "\nTurn " << turn + 1 << ":\n";
        for (Robot* r : robots) {
            if (r->isAlive()) {
                // r->takeTurn(matrix, positionMap);
                r->takeTurn(matrix, robots);
            }
        }
        cout << "\nBattlefield:\n";
        for (const auto& row : matrix) {
            for (char ch : row) cout << ch;
            cout << '\n';
        }
    }

    for (Robot* r : robots) delete r;
    return 0;
}
