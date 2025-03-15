/*
489. Robot Room Cleaner
You are controlling a robot that is located somewhere in a room. The room is modeled as an m x n binary grid where 0 represents a wall and 1 represents an empty slot.

The robot starts at an unknown location in the room that is guaranteed to be empty, and you do not have access to the grid, but you can move the robot using the given API Robot.

You are tasked to use the robot to clean the entire room (i.e., clean every empty cell in the room). The robot with the four given APIs can move forward, turn left, or turn right. Each turn is 90 degrees.

When the robot tries to move into a wall cell, its bumper sensor detects the obstacle, and it stays on the current cell.

Design an algorithm to clean the entire room using the following APIs:

interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}

Note that the initial direction of the robot will be facing up. You can assume all four edges of the grid are all surrounded by a wall.

 

Custom testing:

The input is only given to initialize the room and the robot's position internally. You must solve this problem "blindfolded". In other words, you must control the robot using only the four mentioned APIs without knowing the room layout and the initial robot's position.

Example:

Input:
room = [
  [1,1,1,1,1,0,1,1],
  [1,1,1,1,1,0,1,1],
  [1,0,1,1,1,1,1,1],
  [0,0,0,1,0,0,0,0],
  [1,1,1,1,1,1,1,1]
],
row = 1,
col = 3
Output: Robot cleaned all rooms.
Explanation: All grids in the room are marked by either 0 or 1.
0 means the cell is blocked, while 1 means the cell is accessible.
The robot initially starts at the position of row=1, col=3.
From the top left corner, its position is one row below and three columns right.

Notes:

The input is only given to initialize the room and the robot's position internally. You must solve this problem "blindfolded". In other words, you must control the robot using only the mentioned 4 APIs, without knowing the room layout and the initial robot's position.
The robot's initial position will always be in an accessible cell.
The initial direction of the robot will be facing up.
All accessible cells are connected, which means the all cells marked as 1 will be accessible by the robot.
Assume all four edges of the grid are all surrounded by wall.

Constraints:

m == room.length
n == room[i].length
1 <= m <= 100
1 <= n <= 200
room[i][j] is either 0 or 1.
0 <= row < m
0 <= col < n
room[row][col] == 1
All the empty cells can be visited from the starting position.
*/


/*
Implementing my own robot class so that I can confirm my answer. Basically, I'll create a grid and everytime clean() is called, I'll mark that 
cell as visited/cleaned. At the end, I'll confirm if all empty cells are cleaned or not.
*/
#include <iostream>
// #include <unordered_set>
#include <set>
using namespace std;

class Robot {
    private:
        vector<vector<int> > grid;
        vector<vector<bool> > visited;
        int dir; // 0 is up, 1 is right, 2 is down, 3 is left
        int currentRow, currentCol;
    
        bool move() {
            vector<int> row = {-1, 0, 1, 0};
            vector<int> col = {0, 1, 0, -1}; 
            // according to above, dir=0 means facing/move up, dir=1 means move right, dir=2 means move down, and dir=3 means move left
            int newx = currentRow + row[dir];
            int newy = currentCol + col[dir];
            if(newx < grid.size() && newx >= 0 && newy < grid[0].size() && newy >= 0){
                if(grid[newx][newy]==1){
                    cout << "moved from [" << currentRow << "," << currentCol << "] to [" << newx << "," << newy << "]" << endl;
                    currentRow = newx;
                    currentCol = newy;
                    return true;
                }
            }
            return false;
        }

        void turnLeft() {
            dir -= 1;
            if(dir==-1) dir = 3;
        }

        void turnRight() {
            dir = (dir+1)%4;
        }

        void clean() {
            visited[currentRow][currentCol] = true;
        }
    
    public:
        Robot(vector<vector<int> > grid, int row, int col) {
            this->grid = grid;
            currentRow = row;
            currentCol = col;
            dir = 0;
            visited.resize(grid.size(), vector<bool> (grid[0].size(), false));
        }

        bool isGridClean() {
            for(int i=0; i<grid.size(); i++)
                for(int j=0; j<grid[0].size(); j++)
                    if(grid[i][j]==1 && !visited[i][j])
                        return false;
            return true;
        }

        // FUNCTION THAT YOU NEED TO IMPLEMENT (as part of the question)
        void cleanRoom() {
            /*
            Initial thoughts: My robot isn't aware of where it is. So let's say you are at 0,0. (This 0,0 is not the grid's coordinate,
            rather, it is your new origin. So we can have negative coordinates as well now). We can start doing a dfs traversal. 

            At any node, you have 4 options, either move up (assuming you came from cell below, facing up), or if that is not an option 
            or if you have already explored it, then move right, or move down, or move left. Now you'd wonder, why move down? 
            Well, you won't actually move down if you have already come from down as you'll only go ahead and move if you haven't 
            visited that cell before. Now, once you've explored all options, you want to go back to where you came from, that is, the
            previous cell. 

            Let's consider an example. Suppose you come to (x,y) from (x+1, y). That is, by taking a step upwards. For example, from 
            (3,5), you went up to (2,5).
            So, now, how would this look like? Say you're standing at x,y. First you see if (x-1,y) is not visited and if you can move there.
            If you can, go and clean, and say you somehow come back to (x,y), what would you do next? I'd turn right, and explore (x, y+1). 
            Say you come back to (x,y), but facing right. Now you, turn right again to face down at (x+1, y). In this case, we already came
            from here, so (x+1, y) is already visited. So we don't move there again yet, but instead, turn right again to face (x,y-1). 
            Explore, and now you come back to (0,0) but facing left. So turn right again, and now you're facing up, the original direction 
            with you started. Now, we have explored all 4 directions. Now we gotta go back to (x+1,y) as that is where we had come from.
            To do that, turn right twice, make a move, and turn right twice again, so that when you are at (x+1, y), you are facing the same
            position which you were in when you had started to explore from (x+1,y) towards (x, y).

            This way, basically your robot is exploring all 4 directions, and if blocked, it is turning right twice to face where it came from,
            taking a step in that direction, and turning right twice again to kinda reset. Reset as in, face the direction from where it 
            actually started the dfs for that subtree/recursion tree.

            So by the end of dfs traversal, your robot will come back to the same position as it started from.
            
            Good video are: https://www.youtube.com/watch?v=OyaHANapsh0 and https://www.youtube.com/watch?v=UOKq1tKogB4
            */

            set<vector<int> > visitedCoordinates; // I wanted to use unordered_set but for that we gotta provide our own
            // hash function for vector<int> or pair<int, int>

            // start dfs from current place, and we are facing up
            vector<int> row = {-1, 0, 1, 0}; // up, right, down, left
            vector<int> col = {0, 1, 0, -1};
            dfs(0, 0, 0, visitedCoordinates, row, col); // x, y, dir
        }

        void dfs(int x, int y, int dir, set<vector<int> > &visitedCoordinates, vector<int> &row, vector<int> &col) {
            visitedCoordinates.insert({x, y});
            this->clean();
            // now start exploring all 4 directions. Start with where you're facing, and keep moving right
            for(int i=0; i<4; i++){
                int newDir = (dir+i)%4; // IMPORTANT. See how you're setting the new direction. And that is why setting directions
                // in either clockwise or anticlockwise is so important. If we're facing left initally, we want to try going further 
                // left in the grid first (3 + 0)%4 = 3. Then we want to turn right, and try going up. (3+1)%4 = 0 (which is up direction). 
                // Then we want to turn right and try going right. (3+2)%4 = 1 (which is right). Then we want to turn right and try going
                // down. (3+3)%4 = 2 which is down. Turn right again to face left now at the end.
                int newx = x + row[newDir];
                int newy = y + col[newDir];
                if(visitedCoordinates.find({newx, newy})==visitedCoordinates.end() && this->move()) {
                    // so this means we have already moved to the new cell. Start dfs from there
                    dfs(newx, newy, newDir, visitedCoordinates, row, col);
                    // now when dfs would end for the new cell, we want to come back to current cell (x, y)
                    this->comeBack();
                    // so calling comeBack would bring us back to (x,y) and we would be facing (newx,newy) though.
                }
                this->turnRight(); // keep turning right to explore next direction.
            }
        }

        void comeBack(){
            this->turnRight();
            this->turnRight();
            this->move();
            this->turnRight();
            this->turnRight();
        }

};

int main() {
    Robot robot({{1,1,1,1,1,0,1,1},{1,1,1,1,1,0,1,1},{1,0,1,1,1,1,1,1},{0,0,0,1,0,0,0,0},{1,1,1,1,1,1,1,1}}, 1, 3);
    robot.cleanRoom();
    cout << robot.isGridClean() << endl;
}