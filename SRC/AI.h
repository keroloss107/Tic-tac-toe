#ifndef AI_H
#define AI_H

#include "Board.h"
#include <utility>
#include <vector>
using namespace std;

class AI {
public:
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

    // Tree-based Minimax helper
    struct TreeNode {
        Board boardState;
        pair<int, int> move;
        int score;
        bool isMaximizing;
        vector<TreeNode*> children;

        TreeNode(Board b, pair<int, int> m, bool maximizing)
            : boardState(b), move(m), score(0), isMaximizing(maximizing) {}
    };

    int buildTree(TreeNode* node, int depth, int alpha, int beta);

public:
    AI(char aiMark, char humanMark, Difficulty level);   // Constructor to initialize AI and human marks and difficulty level

    // Function to find the best move for the AI
    pair<int, int> findBestMove(Board& board);
};

#endif  // AI_H
// End of AI.h
// This file contains the definition of the AI class and its methods.