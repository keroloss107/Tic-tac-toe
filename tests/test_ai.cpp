#include <gtest/gtest.h>
#include "../SRC/AI.h"
#include "../SRC/Board.h"

TEST(AITest, EasyModeReturnsValidMove) {
    Board board;
    AI ai('O', 'X', AI::EASY);
    auto move = ai.findBestMove(board);

    EXPECT_GE(move.first, 0);
    EXPECT_LT(move.first, Board::getSize());
    EXPECT_GE(move.second, 0);
    EXPECT_LT(move.second, Board::getSize());
    EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
}

TEST(AITest, HardModeBlocksOpponentWin) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    // X is about to win; O must block at (0, 2)
    board.makeMove(0, 0, 'X');
    board.makeMove(0, 1, 'X');

    auto move = ai.findBestMove(board);
    EXPECT_EQ(move, std::make_pair(0, 2));
}

TEST(AITest, HardModeMakesWinningMove) {
    Board board;
    AI ai('O', 'X', AI::HARD);

    // O can win now by placing at (2, 2)
    board.makeMove(0, 0, 'O');
    board.makeMove(1, 1, 'O');
    board.makeMove(0, 1, 'X');
    board.makeMove(1, 2, 'X');

    auto move = ai.findBestMove(board);
    EXPECT_EQ(move, std::make_pair(2, 2));
}
