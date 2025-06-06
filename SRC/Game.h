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
    void switchPlayer(std::string& currentPlayerName, char& currentPlayerSymbol);
};

#endif // GAME_H
// End of Game.h
// This file contains the definition of the Game class and its methods.