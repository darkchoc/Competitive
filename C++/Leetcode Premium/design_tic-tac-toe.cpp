/*
348. Design Tic-Tac-Toe
Design a Tic-tac-toe game that is played between two players on a n x n grid.

You may assume the following rules:

A move is guaranteed to be valid and is placed on an empty block.
Once a winning condition is reached, no more moves is allowed.
A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
Example:

Given n = 3, assume that player 1 is "X" and player 2 is "O" in the board.

TicTacToe toe = new TicTacToe(3);

toe.move(0, 0, 1); -> Returns 0 (no one wins)
|X| | |
| | | |    // Player 1 makes a move at (0, 0).
| | | |

toe.move(0, 2, 2); -> Returns 0 (no one wins)
|X| |O|
| | | |    // Player 2 makes a move at (0, 2).
| | | |

toe.move(2, 2, 1); -> Returns 0 (no one wins)
|X| |O|
| | | |    // Player 1 makes a move at (2, 2).
| | |X|

toe.move(1, 1, 2); -> Returns 0 (no one wins)
|X| |O|
| |O| |    // Player 2 makes a move at (1, 1).
| | |X|

toe.move(2, 0, 1); -> Returns 0 (no one wins)
|X| |O|
| |O| |    // Player 1 makes a move at (2, 0).
|X| |X|

toe.move(1, 0, 2); -> Returns 0 (no one wins)
|X| |O|
|O|O| |    // Player 2 makes a move at (1, 0).
|X| |X|

toe.move(2, 1, 1); -> Returns 1 (player 1 wins)
|X| |O|
|O|O| |    // Player 1 makes a move at (2, 1).
|X|X|X|

Implement the TicTacToe class:

TicTacToe(int n) Initializes the object the size of the board n.
int move(int row, int col, int player) Indicates that the player with id player plays at the cell (row, col) of the board. The move is guaranteed to be a valid move, and the two players alternate in making moves. Return
0 if there is no winner after the move,
1 if player 1 is the winner after the move, or
2 if player 2 is the winner after the move.

Constraints:

2 <= n <= 100
player is 1 or 2.
0 <= row, col < n
(row, col) are unique for each different call to move.
At most n^2 calls will be made to move.

Follow up:
Could you do better than O(n^2) per move() operation?
*/

/*
Thoughts: 
Option 1: Have 2D grid of characters and anytime a X or O is placed, just check that complete column,
row, and in case the cell is part of any of the two diagonals, then the diagonal(s) as well. 
The move operation would be O(n) in this case. The space complexity will be O(n^2).

Option 2: (BETTER)
I was thinking if we can make it better and I think if we assign +1 to player one and -1 to player two,
and we have a sum for each row, each column, and the two diagonals, then we can add 1 to the row/col and
diagonal (if cell falls in the diagonal) when player 1 makes a move, and subtract 1 when player to makes
a move. If after addition/subtration, the sum becomes +n or -n, it means the player has won.

This would have time complexity of O(1) and space complexity of O(n) as we have n sums for rows,
n sums for columns and 2 sums for diagonals. Let's implement this.
*/

#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
private:
    int n;
    vector<int> rowSum;
    vector<int> colSum;
    int diagonalOneSum;
    int diagonalTwoSum;

public:
    TicTacToe(int n){
        this->n = n;
        rowSum.resize(n, 0);
        colSum.resize(n, 0);
    }

    int move(int row, int col, int player){
        rowSum[row] += (player==1)?1:-1;
        colSum[col] += (player==1)?1:-1;
        // see if it is part of topleft to bottom right diagonal (i==j)
        if(row==col)
            diagonalOneSum += (player==1)?1:-1;
        // see if it is part of topRight to bottom left diagonal (i+j=n-1)
        if(row+col == this->n - 1)
            diagonalTwoSum += (player==1)?1:-1;
        // see if player won
        if(player==1 && (rowSum[row]==n || colSum[col]==n || diagonalOneSum==n || diagonalTwoSum==n))
            return 1;
        if(player==2 && (rowSum[row]==-n || colSum[col]==-n || diagonalOneSum==-n || diagonalTwoSum==-n))
            return 2;
        return 0;
    }
};

int main() {
    // Test 1
    TicTacToe test1(3);
    cout << test1.move(0,0,1) << test1.move(0,2,2) << test1.move(2,2,1) << test1.move(1,1,2) << test1.move(2,0,1) << test1.move(1,0,2) << test1.move(2,1,1) << endl;
    // 0 0 0 0 0 0 1
}