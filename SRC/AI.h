#ifndef AI_H
#define AI_H

#include "Board.h"  // Include Board class to interact with it
#include <utility>          // For std::pair
using namespace std; // Use standard namespace for convenience

class AI {
public:
// Enum to represent difficulty levels
enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};
private:
    char aiMark_;           // AI's mark
    char humanMark_;        // Human player's mark
    Difficulty difficulty_; // AI difficulty level
    // Helper function for easy difficulty (random move)
    pair<int, int> getRandomMove(Board& board);
    // Helper function for medium difficulty (random or optimal move)
    pair<int, int> getMediumMove(Board& board);
    // Minimax algorithm with alpha-beta pruning
    int minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta);
public:
    AI(char aiMark, char humanMark, Difficulty level);   // Constructor to initialize AI and human marks and difficulty level

    // Function to find the best move for the AI
    pair<int, int> findBestMove(Board& board);

};
#endif  // AI_H
// End of AI.h
// This file contains the definition of the AI class and its methods.