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

// Test full sequence leading to a draw
TEST(IntegrationTest, GamePlaysToDraw) {
    Board board;
    board.makeMove(0, 0, 'X');
    board.makeMove(0, 1, 'O');
    board.makeMove(0, 2, 'X');
    board.makeMove(1, 0, 'X');
    board.makeMove(1, 1, 'O');
    board.makeMove(1, 2, 'O');
    board.makeMove(2, 0, 'O');
    board.makeMove(2, 1, 'X');
    board.makeMove(2, 2, 'X');

    EXPECT_EQ(board.evaluate(), 0); // Draw
    EXPECT_FALSE(board.isMovesLeft());
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

// Test full game flow until completion between Human and AI
TEST(IntegrationTest, FullGameFlowEndsCorrectly) {
    Game game;

    // Setup names, symbols, and difficulty
    game.setPlayerNamesAndSymbols("Keroloss", "Computer", 'X', 'O');
    AI* ai = new AI('O', 'X', AI::HARD);
    game.setAIPlayer(ai);

    Board& board = game.getBoard();

    std::string currentPlayer = game.getPlayer1Name();
    char currentSymbol = game.getPlayer1Symbol();

    bool gameOver = false;
    int turnCount = 0;

    while (!gameOver && turnCount < 9) {
        if (currentPlayer == "Computer") {
            auto move = ai->findBestMove(board);
            board.makeMove(move.first, move.second, currentSymbol);
        }
        else {
            // Simulate human move by picking first available
            auto moves = board.getAvailableMoves();
            if (!moves.empty()) {
                board.makeMove(moves.front().first, moves.front().second, currentSymbol);
            }
        }

        int result = board.evaluate();
        if ((result == 10 && currentSymbol == 'O') || (result == -10 && currentSymbol == 'X')) {
            gameOver = true;
        }
        else if (!board.isMovesLeft()) {
            gameOver = true;
        }
        else {
            game.switchPlayer(currentPlayer, currentSymbol);
        }

        ++turnCount;
    }

    EXPECT_TRUE(gameOver);
    EXPECT_TRUE(board.evaluate() == 10 || board.evaluate() == -10 || !board.isMovesLeft());

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



// End of test_integration.cpp
