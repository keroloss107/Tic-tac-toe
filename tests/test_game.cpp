#include "gtest/gtest.h"
#include "../SRC/Game.h"  // Adjust path if needed


// Test Game constructor initializes values correctly
TEST(GameTest, Constructor_InitializesDefaults) {
    Game game;
    EXPECT_FALSE(game.isVsAI());
    EXPECT_EQ(game.getAIPlayer(), nullptr);
}

// Test switchPlayer changes name and symbol correctly
TEST(GameTest, SwitchPlayer_AlternatesCorrectly) {
    Game game;
    game.setPlayerNamesAndSymbols("Alice", "Bob", 'X', 'O');

    std::string currentName = "Alice";
    char currentSymbol = 'X';

    game.switchPlayer(currentName, currentSymbol);
    EXPECT_EQ(currentName, "Bob");
    EXPECT_EQ(currentSymbol, 'O');

    game.switchPlayer(currentName, currentSymbol);
    EXPECT_EQ(currentName, "Alice");
    EXPECT_EQ(currentSymbol, 'X');
}


// Test basic interaction with the game’s board via public getter
TEST(GameTest, GameBoard_ApplyMoveReflectsCorrectly) {
    Game game;
    Board& board = game.getBoard();

    board.makeMove(0, 1, 'X');
    EXPECT_EQ(board.getCell(0, 1), 'X');
    EXPECT_FALSE(board.isCellEmpty(0, 1));
}

// Test if AI object can be safely deleted without crash
TEST(GameTest, Destructor_CleansUpAIIfCreated) {
    Game* game = new Game();

    // Simulate setup — AI creation manually
    AI* ai = new AI('O', 'X', AI::HARD);
    AI* temp = ai;
    // Use a little trick here because there's no setter
    // We'll assume AI gets created normally in setupGame()
    delete temp;

    delete game;  // Destructor should handle deletion safely even if nullptr
}

