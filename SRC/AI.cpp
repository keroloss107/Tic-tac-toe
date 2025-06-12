#include "AI.h"
#include <limits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// Constructor to initialize AI and human marks and difficulty level
AI::AI(char aiMark, char humanMark, Difficulty level) : aiMark_(aiMark), humanMark_(humanMark), difficulty_(level) {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

// Tree node struct definition
struct TreeNode {
    Board boardState;
    pair<int, int> move;
    int score;
    bool isMaximizing;
    vector<TreeNode*> children;

    TreeNode(Board b, pair<int, int> m, bool maximizing)
        : boardState(b), move(m), score(0), isMaximizing(maximizing) {
    }
};

// Helper function for easy difficulty (random move)
pair<int, int> AI::getRandomMove(Board& board) {
    auto moves = board.getAvailableMoves();
    if (!moves.empty()) {
        int randomIndex = rand() % moves.size();
        return moves[randomIndex];
    }
    return { -1, -1 };
}

// Helper for MEDIUM level: sometimes random, sometimes optimal
pair<int, int> AI::getMediumMove(Board& board) {
    if (rand() % 2 == 0) {
        return getRandomMove(board);
    }
    else {
        return findBestMove(board);
    }
}

// Tree-based Minimax build and evaluate
int AI::buildTree(TreeNode* node, int depth, int alpha, int beta) {
    int score = node->boardState.evaluate();
    if (score == 10 || score == -10 || !node->boardState.isMovesLeft()) {
        node->score = score;
        return score;
    }

    if (node->isMaximizing) {
        int bestValue = numeric_limits<int>::min();
        for (auto move : node->boardState.getAvailableMoves()) {
            Board newBoard = node->boardState;
            newBoard.makeMove(move.first, move.second, aiMark_);
            TreeNode* child = new TreeNode(newBoard, move, false);
            int value = buildTree(child, depth + 1, alpha, beta);
            node->children.push_back(child);
            bestValue = max(bestValue, value);
            alpha = max(alpha, bestValue);
            if (beta <= alpha) break;
        }
        node->score = bestValue;
    }
    else {
        int bestValue = numeric_limits<int>::max();
        for (auto move : node->boardState.getAvailableMoves()) {
            Board newBoard = node->boardState;
            newBoard.makeMove(move.first, move.second, humanMark_);
            TreeNode* child = new TreeNode(newBoard, move, true);
            int value = buildTree(child, depth + 1, alpha, beta);
            node->children.push_back(child);
            bestValue = min(bestValue, value);
            beta = min(beta, bestValue);
            if (beta <= alpha) break;
        }
        node->score = bestValue;
    }
    return node->score;
}

// Function to find the best move for the AI
pair<int, int> AI::findBestMove(Board& board) {
    if (difficulty_ == EASY) {
        return getRandomMove(board);
    }
    else if (difficulty_ == MEDIUM) {
        return getMediumMove(board);
    }
    else {
        TreeNode* root = new TreeNode(board, { -1, -1 }, true);
        buildTree(root, 0, numeric_limits<int>::min(), numeric_limits<int>::max());

        pair<int, int> bestMove = { -1, -1 };
        int bestScore = numeric_limits<int>::min();

        for (auto child : root->children) {
            if (child->score > bestScore) {
                bestScore = child->score;
                bestMove = child->move;
            }
        }

        for (auto child : root->children) delete child;
        delete root;

        return bestMove;
    }
}
