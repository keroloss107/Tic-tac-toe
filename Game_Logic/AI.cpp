#include "AI.h"
#include <limits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// Constructor
AI::AI(char aiMark, char humanMark, Difficulty level)
    : aiMark_(aiMark), humanMark_(humanMark), difficulty_(level) {
    srand(static_cast<unsigned int>(time(0)));
}

// Main interface
pair<int, int> AI::findBestMove(Board& board) {
    auto availableMoves = board.getAvailableMoves();
    if (availableMoves.empty()) {
        return { -1, -1 };  // No possible moves
    }
    if (difficulty_ == EASY) {
        return getRandomMove(board);
    }
    else if (difficulty_ == MEDIUM) {
        return getMediumMove(board);
    }
    else { // HARD
        return runFullMinimax(board);
    }
}

// ===================================
// EASY: Random Move
// ===================================
pair<int, int> AI::getRandomMove(Board& board) {
    auto moves = board.getAvailableMoves();
    if (!moves.empty()) {
        int randomIndex = rand() % moves.size();
        return moves[randomIndex];
    }
    return { -1, -1 };
}

// ===================================
// MEDIUM: shallow Minimax with Depth Limit 2
// ===================================
pair<int, int> AI::getMediumMove(Board& board) {
        return findBestMoveLimited(board, 2);
}

// Shallow minimax with depth limit
pair<int, int> AI::findBestMoveLimited(Board& board, int maxDepth) {

    auto availableMoves = board.getAvailableMoves();
    if (availableMoves.empty()) {
        return { -1, -1 };
    }

    TreeNode* root = new TreeNode(board, { -1, -1 }, true);
    buildTreeLimited(root, 0, maxDepth, numeric_limits<int>::min(), numeric_limits<int>::max());

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

// ===================================
// HARD: Full-depth Minimax
// ===================================
pair<int, int> AI::runFullMinimax(Board& board) {
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

// ===================================
// Full-depth Minimax (Hard)
// ===================================
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

// ===================================
// Depth-Limited Minimax (Medium)
// ===================================
int AI::buildTreeLimited(TreeNode* node, int depth, int maxDepth, int alpha, int beta) {
    int score = node->boardState.evaluate();
    if (score == 10 || score == -10 || !node->boardState.isMovesLeft() || depth == maxDepth) {
        node->score = score;
        return score;
    }

    if (node->isMaximizing) {
        int bestValue = numeric_limits<int>::min();
        for (auto move : node->boardState.getAvailableMoves()) {
            Board newBoard = node->boardState;
            newBoard.makeMove(move.first, move.second, aiMark_);
            TreeNode* child = new TreeNode(newBoard, move, false);
            int value = buildTreeLimited(child, depth + 1, maxDepth, alpha, beta);
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
            int value = buildTreeLimited(child, depth + 1, maxDepth, alpha, beta);
            node->children.push_back(child);
            bestValue = min(bestValue, value);
            beta = min(beta, bestValue);
            if (beta <= alpha) break;
        }
        node->score = bestValue;
    }

    return node->score;
}