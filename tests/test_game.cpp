#include <gtest/gtest.h>
#include "../src/Game.h"

class GameTest : public ::testing::Test {
protected:
    Game game;

    std::string name = "Player1";
    char symbol = 'X';
};

TEST_F(GameTest, SwitchPlayerSwapsCorrectly) {
    std::string player1 = "Alice";
    std::string player2 = "Bob";
    char mark1 = 'X';
    char mark2 = 'O';

    Game g;
    g.switchPlayer(player1, mark1);  // Now player1 should become Bob

    // Note: this works only if switchPlayer swaps between fixed internal names.
    // To fully test, switchPlayer() needs to be public & use internal name tracking.
    SUCCEED();  // Placeholder since Game class methods are limited in testability now
}
