#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "AI.h"
#include <string>

class Game {
public:
    Game();
    ~Game();

    // Make setupGame PUBLIC
    void setupGame(std::string player1Name, std::string player2Name, char player1Symbol, bool vsAI, AI::Difficulty difficulty = AI::EASY);

    void switchPlayer(std::string& currentPlayerName, char& currentPlayerSymbol);

    // === ADD these getters ===
    Board& getBoard() { return board_; }
    AI* getAI() { return aiPlayer_; }
    std::string getPlayer1Name() const { return player1Name_; }
    std::string getPlayer2Name() const { return player2Name_; }
    char getPlayer1Symbol() const { return player1Symbol_; }
    char getPlayer2Symbol() const { return player2Symbol_; }
    bool isVsAI() const { return vsAI_; }

private:
    Board board_;
    AI* aiPlayer_;
    std::string player1Name_;
    std::string player2Name_;
    char player1Symbol_;
    char player2Symbol_;
    bool vsAI_;
    AI::Difficulty aiDifficulty_;
};

#endif // GAME_H

