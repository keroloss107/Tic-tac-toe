#include "gtest/gtest.h"
#include "../include/Board.h"  // Adjust the include path based on your project structure


// Test Board Constructor and initial state
TEST(BoardTest, Constructor_InitializesEmptyBoard) {
    Board board;
    for (int i = 0; i < Board::getSize(); ++i) {
        for (int j = 0; j < Board::getSize(); ++j) {
            EXPECT_TRUE(board.isCellEmpty(i, j));
            EXPECT_EQ(board.getCell(i, j), ' ');
        }
    }
}

// Test isMovesLeft on a new board
TEST(BoardTest, IsMovesLeft_NewBoard_ReturnsTrue) {
    Board board;
    EXPECT_TRUE(board.isMovesLeft());
}

// Test isMovesLeft on a full board
TEST(BoardTest, IsMovesLeft_FullBoard_ReturnsFalse) {
    Board board;
    for (int i = 0; i < Board::getSize(); ++i)
        for (int j = 0; j < Board::getSize(); ++j)
            board.makeMove(i, j, 'X');
    EXPECT_FALSE(board.isMovesLeft());
}

// Test makeMove and getCell
TEST(BoardTest, MakeMove_ValidMove_SetsCell) {
    Board board;
    board.makeMove(1, 1, 'X');
    EXPECT_EQ(board.getCell(1, 1), 'X');
}

// Test makeMove on invalid cell
TEST(BoardTest, MakeMove_InvalidMove_DoesNotChangeCell) {
    Board board;
    board.makeMove(0, 0, 'X');
    board.makeMove(0, 0, 'O');  // Invalid: already occupied
    EXPECT_EQ(board.getCell(0, 0), 'X');
}

// Test undoMove
TEST(BoardTest, UndoMove_ResetsCellToEmpty) {
    Board board;
    board.makeMove(0, 0, 'O');
    board.undoMove(0, 0);
    EXPECT_TRUE(board.isCellEmpty(0, 0));
}

// Test evaluate for row win
TEST(BoardTest, Evaluate_RowWin_ReturnsCorrectScore) {
    Board board;
    board.makeMove(0, 0, 'O');
    board.makeMove(0, 1, 'O');
    board.makeMove(0, 2, 'O');
    EXPECT_EQ(board.evaluate(), 10);  // AI wins
}

// Test evaluate for column win
TEST(BoardTest, Evaluate_ColumnWin_ReturnsCorrectScore) {
    Board board;
    board.makeMove(0, 1, 'X');
    board.makeMove(1, 1, 'X');
    board.makeMove(2, 1, 'X');
    EXPECT_EQ(board.evaluate(), -10);  // Player wins
}

// Test evaluate for diagonal win
TEST(BoardTest, Evaluate_DiagonalWin_ReturnsCorrectScore) {
    Board board;
    board.makeMove(0, 0, 'O');
    board.makeMove(1, 1, 'O');
    board.makeMove(2, 2, 'O');
    EXPECT_EQ(board.evaluate(), 10);  // AI wins
}

// Test evaluate for anti-diagonal win
TEST(BoardTest, Evaluate_AntiDiagonalWin_ReturnsCorrectScore) {
    Board board;
    board.makeMove(0, 2, 'X');
    board.makeMove(1, 1, 'X');
    board.makeMove(2, 0, 'X');
    EXPECT_EQ(board.evaluate(), -10);  // Player wins
}

// Test evaluate with no winner
TEST(BoardTest, Evaluate_NoWin_ReturnsZero) {
    Board board;
    board.makeMove(0, 0, 'O');
    board.makeMove(0, 1, 'X');
    board.makeMove(0, 2, 'O');
    EXPECT_EQ(board.evaluate(), 0);  // No winner
}

// Test getAvailableMoves
TEST(BoardTest, GetAvailableMoves_PartiallyFilledBoard_ReturnsCorrectMoves) {
    Board board;
    board.makeMove(0, 0, 'X');
    board.makeMove(1, 1, 'O');
    auto moves = board.getAvailableMoves();
    EXPECT_EQ(moves.size(), 7);
    for (auto& move : moves) {
        EXPECT_TRUE(board.isCellEmpty(move.first, move.second));
    }
}
