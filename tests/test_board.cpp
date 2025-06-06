#include <gtest/gtest.h>
#include "../SRC/Board.h"

// ✅ Test: Constructor initializes all cells to non-player characters
TEST(BoardTest, BoardStartsEmpty) {
    Board board;
    for (int row = 0; row < Board::getSize(); ++row) {
        for (int col = 0; col < Board::getSize(); ++col) {
            EXPECT_TRUE(board.isCellEmpty(row, col)) << "Cell (" << row << "," << col << ") should be empty";
        }
    }
}

// ✅ Test: makeMove fills a cell, and isCellEmpty reflects it
TEST(BoardTest, ValidMoveFillsCell) {
    Board board;
    board.makeMove(1, 1, 'X');
    EXPECT_FALSE(board.isCellEmpty(1, 1));
    EXPECT_EQ(board.getCell(1, 1), 'X');
}

// ✅ Test: undoMove clears a cell
TEST(BoardTest, UndoMoveClearsCell) {
    Board board;
    board.makeMove(0, 0, 'O');
    board.undoMove(0, 0);
    EXPECT_TRUE(board.isCellEmpty(0, 0));
}

// ✅ Test: isMovesLeft returns false when all cells are filled
TEST(BoardTest, NoMovesLeftOnFullBoard) {
    Board board;
    for (int i = 0; i < Board::getSize(); ++i) {
        for (int j = 0; j < Board::getSize(); ++j) {
            board.makeMove(i, j, 'X');
        }
    }
    EXPECT_FALSE(board.isMovesLeft());
}

// ✅ Test: getAvailableMoves returns correct empty cells
TEST(BoardTest, GetAvailableMovesCorrectly) {
    Board board;
    board.makeMove(0, 0, 'X');
    board.makeMove(1, 1, 'O');
    
    auto moves = board.getAvailableMoves();
    EXPECT_EQ(moves.size(), 7);  // 9 total - 2 filled
    for (const auto& move : moves) {
        EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
    }
}

// ✅ Test: evaluate returns correct score for a win (assumes 'X' wins)
TEST(BoardTest, EvaluateDetectsWin) {
    Board board;
    board.makeMove(0, 0, 'X');
    board.makeMove(0, 1, 'X');
    board.makeMove(0, 2, 'X');
    EXPECT_EQ(board.evaluate(), -10); // Assuming 'X' is AI
}

// ✅ Test: getCell returns correct value
TEST(BoardTest, GetCellReadsCorrectly) {
    Board board;
    board.makeMove(2, 2, 'O');
    EXPECT_EQ(board.getCell(2, 2), 'O');
}
