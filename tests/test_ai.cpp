#include "gtest/gtest.h"
#include "../include/AI.h"
#include "../include/Board.h"

// ======================================
// EASY MODE TESTS
// ======================================

TEST(AITest, EasyMode_ReturnsRandomValidMove) {
    Board board;
    AI ai('O', 'X', AI::EASY);

    board.makeMove(0, 0, 'X'); // Simulate some moves
    auto move = ai.findBestMove(board);  // Internally calls getRandomMove

    // The move must be a valid empty cell
    EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
}

// ======================================
// MEDIUM MODE TESTS
// ======================================

TEST(AITest, MediumMode_MakesValidMove) {
    Board board;
    AI ai('O', 'X', AI::MEDIUM);

    board.makeMove(0, 0, 'X');
    board.makeMove(1, 1, 'O');

    auto move = ai.findBestMove(board);  // Internally calls getMediumMove
    EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
}

TEST(AITest, MediumMode_BlocksImmediateThreat) {
    Board board;
    AI ai('O', 'X', AI::MEDIUM);

    // Human is about to win
    board.makeMove(0, 0, 'X');
    board.makeMove(0, 1, 'X');

    auto move = ai.findBestMove(board);
    board.makeMove(move.first, move.second, 'O');

    // After AI move, human should not win
    EXPECT_NE(board.evaluate(), -10);
}

// ======================================
// HARD MODE TESTS
// ======================================

TEST(AITest, HardMode_WinningMoveDetected) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    // O can win
    board.makeMove(0, 0, 'O');
    board.makeMove(0, 1, 'O');
    board.makeMove(1, 0, 'X');
    board.makeMove(1, 1, 'X');

    auto move = ai.findBestMove(board);  // Uses full minimax
    board.makeMove(move.first, move.second, 'O');

    // Should now be a winning move
    EXPECT_EQ(board.evaluate(), 10);
}

TEST(AITest, HardMode_BlocksOpponentWin) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    // X is about to win at (0,2)
    board.makeMove(0, 0, 'X');
    board.makeMove(0, 1, 'X');

    auto move = ai.findBestMove(board);
    board.makeMove(move.first, move.second, 'O');

    EXPECT_NE(board.evaluate(), -10);  // AI should block
}


TEST(AITest, HardMode_ChoosesValidMoveOnEmptyBoard) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    auto move = ai.findBestMove(board);  // First move
    EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
}

TEST(AITest, HardMode_NoCrashOnFullBoard) {
    Board board;

    // Fill the board with a draw scenario (no winner, no empty spots)
    board.makeMove(0, 0, 'X'); board.makeMove(0, 1, 'O'); board.makeMove(0, 2, 'X');
    board.makeMove(1, 0, 'X'); board.makeMove(1, 1, 'O'); board.makeMove(1, 2, 'O');
    board.makeMove(2, 0, 'O'); board.makeMove(2, 1, 'X'); board.makeMove(2, 2, 'X');

    AI ai('O', 'X', AI::HARD);
    auto move = ai.findBestMove(board);

    EXPECT_EQ(move.first, -1);
    EXPECT_EQ(move.second, -1);
}




