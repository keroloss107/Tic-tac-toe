#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "AI.h"
#include <string>

class Game {
public:
    Game();
    ~Game();
    void play();

    const std::string& getPlayer1Name() const { return player1Name_; }
    const std::string& getPlayer2Name() const { return player2Name_; }
    char getPlayer1Symbol() const { return player1Symbol_; }
    char getPlayer2Symbol() const { return player2Symbol_; }
    bool isVsAI() const { return vsAI_; }
    AI* getAIPlayer() const { return aiPlayer_; }
    Board& getBoard() { return board_; }
    void switchPlayer(std::string& currentPlayerName, char& currentPlayerSymbol);
private:
    Board board_;
    AI* aiPlayer_;
    std::string player1Name_;
    std::string player2Name_;
    char player1Symbol_;
    char player2Symbol_;
    bool vsAI_;
    AI::Difficulty aiDifficulty_;

    void setupGame();
};

#endif // GAME_H
// End of Game.h
// This file contains the definition of the Game class and its methods.