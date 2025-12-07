#include <iostream>
using namespace std;

int main() {    

    vector<vector<int>> makeMove(vector<vector<int>>& board, string direction);
    void displayBoard(vector<vector<int>>& board);

    vector<vector<int>> board = {
        {2,0,2,4},
        {0,4,0,4},
        {2,2,2,2},
        {0,0,0,2}
    };
    string x;
    while (true) {
        cout << "BOARD\n";
        displayBoard(board);
        cout << "Move Direction: ";
        cin >> x;
        if (x=="q") break;
        board = makeMove(board, x);
    };
}