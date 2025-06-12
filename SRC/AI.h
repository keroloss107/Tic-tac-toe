#ifndef AI_H
#define AI_H

#include "Board.h"
#include <utility>

class AI {
public:
    enum Difficulty { EASY, MEDIUM, HARD };

    AI(char aiMark, char humanMark, Difficulty level);

    // Main interface: call this to get the AI's chosen move based on difficulty
    std::pair<int, int> findBestMove(Board& board);

private:
    char aiMark_;
    char humanMark_;
    Difficulty difficulty_;

    // === Difficulty-specific helpers ===
    std::pair<int, int> getRandomMove(Board& board);                // For EASY
    std::pair<int, int> getMediumMove(Board& board);                // For MEDIUM
    std::pair<int, int> findBestMoveLimited(Board& board, int maxDepth); // Shallow minimax (used in MEDIUM)
    std::pair<int, int> runFullMinimax(Board& board);               // Full minimax for HARD
    // === Internal node representation ===
    struct TreeNode {
        Board boardState;
        std::pair<int, int> move;
        int score;
        bool isMaximizing;
        std::vector<TreeNode*> children;

        TreeNode(Board b, std::pair<int, int> m, bool maximizing)
            : boardState(b), move(m), score(0), isMaximizing(maximizing) {
        }
    };
    // === Minimax tree functions ===
    int buildTree(TreeNode* node, int depth, int alpha, int beta); // Full-depth minimax (HARD)
    int buildTreeLimited(TreeNode* node, int depth, int maxDepth, int alpha, int beta); // Depth-limited minimax (MEDIUM)


};

#endif // AI_H
