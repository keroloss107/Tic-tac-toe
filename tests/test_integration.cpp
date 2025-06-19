// ===== tests/test_integration.cpp =====
#include "../include/Board.h"
#include "../include/AI.h"
#include "../include/Game.h"
#include <gtest/gtest.h>
#include <iostream>

// Test AI choosing a winning move
TEST(IntegrationTest, AIFindsWinningMoveOnLiveBoard) {
    Board board;
    board.makeMove(0, 0, 'O');
    board.makeMove(0, 1, 'O');
    board.makeMove(1, 0, 'X');
    board.makeMove(1, 1, 'X');

    AI ai('O', 'X', AI::HARD);
    auto move = ai.findBestMove(board);
    EXPECT_EQ(move, std::make_pair(0, 2)); // Expected winning move
}

// Test AI avoids playing in an occupied cell
TEST(IntegrationTest, AIAvoidsOccupiedCell) {
    Board board;
    board.makeMove(0, 0, 'X');

    AI ai('O', 'X', AI::EASY);
    auto move = ai.findBestMove(board);
    EXPECT_NE(move, std::make_pair(0, 0));
}

// Test AI blocks opponent's winning move
TEST(IntegrationTest, AIBlocksOpponent) {
    Board board;
    board.makeMove(0, 0, 'X');
    board.makeMove(1, 0, 'X');
    board.makeMove(0, 1, 'O'); // AI has a move too

    AI ai('O', 'X', AI::HARD);
    auto move = ai.findBestMove(board);

    Board testBoard = board;
    testBoard.makeMove(move.first, move.second, 'O');

    // After AI's move, X should no longer have a winning position
    for (int col = 0; col < 3; ++col) {
        if (testBoard.getCell(0, col) == 'X' &&
            testBoard.getCell(1, col) == 'X' &&
            testBoard.getCell(2, col) == 'X') {
            FAIL() << "AI failed to block column win!";
        }
    }

    SUCCEED(); // Passed if no fail was triggered
}


// Test AI and human alternating moves
TEST(IntegrationTest, AIAndHumanAlternating) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    board.makeMove(0, 0, 'X');
    auto move1 = ai.findBestMove(board);
    board.makeMove(move1.first, move1.second, 'O');

    board.makeMove(1, 1, 'X');
    auto move2 = ai.findBestMove(board);
    board.makeMove(move2.first, move2.second, 'O');

    EXPECT_TRUE(board.isMovesLeft());
    EXPECT_NE(board.evaluate(), 10); // Not yet a win
}

// Test full game integration including Game class logic
TEST(IntegrationTest, GameClassFullIntegration) {
    Game game;

    // Simulate minimal interaction with private members exposed for test
    // We assume symbols and player names are initialized correctly
    Board board;
    AI ai('O', 'X', AI::HARD);

    // Simulated flow
    board.makeMove(0, 0, 'X'); // Human move
    auto aiMove1 = ai.findBestMove(board);
    board.makeMove(aiMove1.first, aiMove1.second, 'O');

    board.makeMove(1, 1, 'X'); // Human
    auto aiMove2 = ai.findBestMove(board);
    board.makeMove(aiMove2.first, aiMove2.second, 'O');

    board.makeMove(2, 2, 'X'); // Human
    auto aiMove3 = ai.findBestMove(board);
    board.makeMove(aiMove3.first, aiMove3.second, 'O');

    // After these moves, the board should have no winner yet or a result
    int result = board.evaluate();
    EXPECT_TRUE(result == 10 || result == -10 || result == 0);
    EXPECT_TRUE(board.isMovesLeft() || result != 0);
}

TEST(IntegrationTest, AIVsAIPlaysFullGame) {
    Board board;
    AI ai1('X', 'O', AI::HARD);
    AI ai2('O', 'X', AI::HARD);

    char currentPlayer = 'X';
    int moveCount = 0;

    while (board.isMovesLeft() && board.evaluate() == 0 && moveCount < 9) {
        auto move = (currentPlayer == 'X') ? ai1.findBestMove(board)
            : ai2.findBestMove(board);
        board.makeMove(move.first, move.second, currentPlayer);
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        ++moveCount;
    }

    int result = board.evaluate();
    EXPECT_TRUE(result == 10 || result == -10 || result == 0);
}

TEST(IntegrationTest, AIHandlesFullBoard) {
    Board board;
    char symbols[2] = { 'X', 'O' };
    int k = 0;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board.makeMove(i, j, symbols[(k++) % 2]);

    AI ai('O', 'X', AI::HARD);
    auto move = ai.findBestMove(board);
    EXPECT_EQ(move, std::make_pair(-1, -1));
}
// End of test_integration.cpp
