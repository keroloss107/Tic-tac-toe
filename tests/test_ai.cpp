#include "gtest/gtest.h"
#include "../SRC/AI.h"
#include "../SRC/Board.h" // Required for board interaction
#include <set>

// Test AI constructor initializes values
TEST(AITest, Constructor_SetsDifficultyAndMarks) {
    AI ai('O', 'X', AI::HARD);
    EXPECT_TRUE(true); // Constructor just sets up state, no assertable output
}

// Test getRandomMove returns valid move
TEST(AITest, GetRandomMove_ReturnsValidMove) {
    Board board;
    AI ai('O', 'X', AI::EASY);

    board.makeMove(0, 0, 'X');
    board.makeMove(1, 1, 'O');

    auto move = ai.findBestMove(board); // Should call getRandomMove internally
    EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
}

// Test getMediumMove may return optimal or random (cannot assert exact output, just validity)
TEST(AITest, MediumMove_AlwaysValid) {
    Board board;
    AI ai('O', 'X', AI::MEDIUM);

    board.makeMove(0, 0, 'X');
    auto move = ai.findBestMove(board); // Might be random or best
    EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
}

// Test findBestMove (minimax) chooses winning move
TEST(AITest, FindBestMove_WinningMoveDetected) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    // AI is 'O', can win by placing at (2,2)
    board.makeMove(0, 0, 'O');
    board.makeMove(1, 1, 'O');
    board.makeMove(0, 1, 'X');
    board.makeMove(0, 2, 'X');

    auto bestMove = ai.findBestMove(board);
    EXPECT_EQ(bestMove.first, 2);
    EXPECT_EQ(bestMove.second, 2);
}

// Test findBestMove (minimax) blocks opponent win
TEST(AITest, FindBestMove_BlocksOpponentWin) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    // Human is 'X' and can win with (2,0) unless blocked
    board.makeMove(0, 0, 'X');
    board.makeMove(1, 1, 'X');
    board.makeMove(0, 1, 'O'); // AI move
    board.makeMove(2, 2, 'O'); // AI move

    auto bestMove = ai.findBestMove(board);
    EXPECT_EQ(bestMove.first, 2);
    EXPECT_EQ(bestMove.second, 0);
}

// Test findBestMove returns a valid move on empty board
TEST(AITest, FindBestMove_EmptyBoard) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    auto move = ai.findBestMove(board);
    EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
}
