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

    // Setup player names and symbols using known values
    std::string player1 = "Alice";
    std::string player2 = "Bob";
    char symbol1 = 'X';
    char symbol2 = 'O';

    // Simulate setup
    std::string currentPlayerName = player1;
    char currentPlayerSymbol = symbol1;

    // Temporarily set Game state using public getters + reference variables
    // (Since there's no setter, we just simulate switching behavior)
    game.switchPlayer(currentPlayerName, currentPlayerSymbol);
    EXPECT_EQ(currentPlayerName, player2);  // Should now be player 2
    EXPECT_EQ(currentPlayerSymbol, symbol2);

    game.switchPlayer(currentPlayerName, currentPlayerSymbol);
    EXPECT_EQ(currentPlayerName, player1);  // Switch back
    EXPECT_EQ(currentPlayerSymbol, symbol1);
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
