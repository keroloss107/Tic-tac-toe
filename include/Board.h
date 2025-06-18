#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <utility> // For std::pair
using namespace std;
class Board
{
public:
private:
    static const int SIZE = 3; // Size of the board (3x3 for Tic-Tac-Toe)
    char grid[SIZE][SIZE]; // 2D array for the board
public:
    Board(); // Constructor to initialize the board
    bool isMovesLeft() const; // Function to check if there are any moves left
    int  evaluate(); // Function to evaluate the board
    void makeMove(int row, int col, char player); // Function to make a move
    void undoMove(int row, int col); // Function to undo a move(for backtracking in minimax)
    void display(); // Function to display the board
    bool isCellEmpty(int row, int col) const; // Function to check if a cell is empty
    static int getSize();       // Static function to access SIZE
    char getCell(int row, int col) const;  // Function to read a specific cell
    vector<pair<int, int>> getAvailableMoves() const; // Function to get all available moves
    ~Board(); // Destructor
};
#endif // BOARD_H
// End of Board.h
// This file contains the definition of the Board class and its methods.
