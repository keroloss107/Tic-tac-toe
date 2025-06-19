#include <iostream>
#include "Board.h"
#include <vector> // For std::vector
using namespace std;

// Constructor: initialize the grid to empty spaces
Board::Board() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            grid[i][j] = ' ';  // Initialize all cells to empty spaces
}
// Check if there are any moves left on the board
bool Board::isMovesLeft() const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == ' ') { // Check if the cell is empty
                return true; // Found an empty cell
            }
        }
    }
    return false; // No empty cells found
}
// Check if any cell is empty (true if moves left)
bool Board::isCellEmpty(int row, int col) const {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        return (grid[row][col] == ' ');  // Found an empty cell
    }
    return false;   // No empty cells found 
}
// Evaluate the board and return score
int Board::evaluate() {
    // Check rows for a win
    for (int row = 0; row < SIZE; ++row) {
        if (grid[row][0] == grid[row][1] && grid[row][1] == grid[row][2]) {
            if (grid[row][0] == 'O') return +10; // AI wins
            else if (grid[row][0] == 'X') return -10; // Player wins
        }
    }
    // Check columns for a win
    for (int col = 0; col < SIZE; ++col) {
        if (grid[0][col] == grid[1][col] && grid[1][col] == grid[2][col]) {
            if (grid[0][col] == 'O') return +10; // AI wins
            else if (grid[0][col] == 'X') return -10; // Player wins
        }
    }
    // Check diagonals for a win
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        if (grid[0][0] == 'O') return +10; // AI wins
        else if (grid[0][0] == 'X') return -10; // Player wins
    }
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        if (grid[0][2] == 'O') return +10; // AI wins
        else if (grid[0][2] == 'X') return -10; // Player wins
    }
    return 0; // No winner yet
}
// Make a move on the board
void Board::makeMove(int row, int col, char player) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && grid[row][col] == ' ') {
        grid[row][col] = player; // Place the player's symbol on the board
    }
    else {
        cout << "Invalid move!" << endl; // Invalid move message
    }
}
// Undo a move on the board
void Board::undoMove(int row, int col) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        grid[row][col] = ' '; // Reset the cell to empty space
    }
}
// Display the board
void Board::display() {
    cout << "Current board:" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << (grid[i][j] == ' ' ? '.' : grid[i][j]) << " "; // Display '.' for empty cells
        }
        cout << endl; // New line after each row
    }
    cout << endl; // New line after completing the whole grid
}
// Static function to access SIZE
int Board::getSize() {
    return SIZE;
}
// Function to read a specific cell
char Board::getCell(int row, int col) const {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        return grid[row][col];
    }
    return ' '; // Return empty if out of bounds
}
// Function to get all available moves
vector<pair<int, int>> Board::getAvailableMoves() const {
    vector<pair<int, int>> moves;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == ' ') {
                moves.emplace_back(i, j);
            }
        }
    }
    return moves;
}
// Destructor
Board::~Board() {
    // No dynamic memory to clean up
}
// End of Board.cpp
// This file contains the implementation of the Board class methods.