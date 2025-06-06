#include "AI.h"
#include <limits>  // For INT_MIN and INT_MAX
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding random number generator
#include <iostream>
#include <vector>  // For std::vector
using namespace std;

// Constructor to initialize AI and human marks and difficulty level
AI::AI(char aiMark, char humanMark, Difficulty level): aiMark_(aiMark), humanMark_(humanMark), difficulty_(level) {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}
// Helper function for easy difficulty (random move)
pair<int, int> AI::getRandomMove(Board& board) {
    auto moves = board.getAvailableMoves();
    if (!moves.empty()) {
        int randomIndex = rand() % moves.size(); // Get a random index
        return moves[randomIndex]; // Return the random move
    }
    return {-1, -1}; // if no moves are available
}
// Helper for MEDIUM level: sometimes random, sometimes optimal
pair<int, int> AI::getMediumMove(Board& board) {
    if (rand() % 2 == 0) { // 50% chance to return a random move, , 50% chance to make the best move
        return getRandomMove(board); // Random move
    } 
    else {  
        return findBestMove(board); // Optimal move
    }
}
// Function to find the best move for the AI
pair<int, int> AI::findBestMove(Board& board) {
    if (difficulty_ == EASY) {
        return getRandomMove(board);    // Easy difficulty: Random move
    } 
    else if (difficulty_ == MEDIUM) {
        return getMediumMove(board);    // Medium difficulty: Random or optimal move
    } 
    else { // Hard difficulty: Use Minimax with Alpha-Beta Pruning
        int bestScore = numeric_limits<int>::min();
        pair<int, int> bestMove = {-1, -1};
        auto availableMoves = board.getAvailableMoves();
        for (const auto& move : availableMoves) {
            board.makeMove(move.first, move.second, aiMark_); // Make the move
            int score = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max()); // Evaluate the move
            board.undoMove(move.first, move.second); // Undo the move
            // Update the best move if the current move is better
            if (score > bestScore) {
                bestScore = score; // Update best score
                bestMove = move;   // Update best move
            }            
        }
        return bestMove; // Return the best move found
}
}
// Minimax algorithm with alpha-beta pruning
int AI::minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta) {
    int score = board.evaluate(); // Evaluate the board
    // Base cases: If the game is over, return the score
    if (score == 10) return score - depth; // AI wins
    if (score == -10) return score + depth; // Player wins
    if (!board.isMovesLeft()) return 0; // No moves left, it's a draw

    if (isMaximizing) { // Maximizing player's turn (AI)
        int bestValue = numeric_limits<int>::min();

        // Loop through all possible moves
        auto availableMoves = board.getAvailableMoves();
        for (const auto& move : availableMoves) {
            board.makeMove(move.first, move.second, aiMark_); // Make the move
            bestValue = max(bestValue, minimax(board, depth + 1, false, alpha, beta)); // Recursively call minimax
            board.undoMove(move.first, move.second); // Undo the move
            alpha = max(alpha, bestValue); // Update alpha value
            if (beta <= alpha) break; // Alpha-Beta Pruning
        }
        return bestValue; // Return the best value found
    } 
    else { // Minimizing player's turn (human)
        int bestValue = numeric_limits<int>::max();
        auto availableMoves = board.getAvailableMoves();
        for (const auto& move : availableMoves) {
            board.makeMove(move.first, move.second, humanMark_); // Make the move
            bestValue = min(bestValue, minimax(board, depth + 1, true, alpha, beta)); // Recursively call minimax
            board.undoMove(move.first, move.second); // Undo the move
            beta = min(beta, bestValue); // Update beta value
            if (beta <= alpha) break; // Alpha-Beta Pruning
        }
        return bestValue; // Return the best value found
    }
}
// End of AI.cpp
// This file contains the implementation of the AI class and its methods.