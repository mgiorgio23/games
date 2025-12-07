#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

using namespace std;
static mt19937 rng(random_device{}());

void displayBoard(vector<vector<int>>& board) {
    for (auto&row : board) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
}

vector<int> compressRow(vector<int>& row) {
    vector<int> newRow;
    for (int i=0; i<row.size();i++) {
        if (row[i] != 0) {
            newRow.push_back(row[i]);
        }
    }
    while (newRow.size() < row.size()) {
        newRow.push_back(0);
    }

    return newRow;
}

vector<int> mergeRow(vector<int> row) {
    for (int i=0; i<row.size()-1;i++) {
        if (row[i]!=0 && row[i] == row[i+1]) {
            row[i] *= 2;
            row[i+1] = 0;
        }
    }
    return row;
}

vector<vector<int>> counterClockwise(vector<vector<int>>& board) {
    int N = board.size();
    vector<vector<int>> newBoard(N, vector<int>(N));

    for (int r=0; r<N; r++) {
        for (int c=0; c<N; c++) {
            newBoard[N-1-c][r] = board[r][c];
        }
    }
    // cout << "Counter Clockwise\n";
    // displayBoard(newBoard);
    return newBoard;
}

vector<vector<int>> clockwise(vector<vector<int>>& board) {
    int N = board.size();
    vector<vector<int>> newBoard(N, vector<int>(N));

    for (int r=0; r<N; r++) {
        for (int c=0; c<N; c++) {
            newBoard[c][N-r-1] = board[r][c];
        }
    }
    // cout << "Clockwise\n";
    // displayBoard(newBoard);
    return newBoard;
}

vector<vector<int>> slide(vector<vector<int>>& board) {
    vector<vector<int>> newBoard = board;

    for (auto& row : newBoard) {
        row = compressRow(row);
        row = mergeRow(row);
        row = compressRow(row);
    }

    return newBoard;
}

void addRandomTile(vector<vector<int>>& board) {
    std::mt19937 rng(random_device{}());
    int N = board.size();
    vector<pair<int,int>> empties;

    for (int r=0;r<N; r++) {
        for (int c=0;c<N; c++) {
            if (board[r][c] == 0) empties.push_back({r,c});
        }
    }
    
    uniform_int_distribution<int> pick(0, empties.size()-1);
    pair<int,int> cell = empties[pick(rng)];
    int row = cell.first;
    int col = cell.second;
    uniform_int_distribution<int> ten(1,10);
    board[row][col] = (ten(rng) == 1 ? 4 : 2);
}

vector<vector<int>> makeMove(vector<vector<int>>& board, string direction) {
    if (direction == "right") {
        board = clockwise(board);
        board = clockwise(board);
        board = slide(board);
        board = counterClockwise(board);
        board = counterClockwise(board);
    } else if (direction == "down") {
        board = clockwise(board);
        board = slide(board);
        board = counterClockwise(board);
    } else if (direction == "left") {
        board = slide(board);
    } else if (direction == "up") {
        board = counterClockwise(board);
        board = slide(board);
        board = clockwise(board);
    } else {
        return board;
    }
    addRandomTile(board);
    return board;
}