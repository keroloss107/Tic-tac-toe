#include "Game.h"
#include <iostream>
#include <utility>
using namespace std;

// Constructor
Game::Game() : aiPlayer_(nullptr), vsAI_(false) {}

// Destructor
Game::~Game() {
    if (aiPlayer_ != nullptr) {
        delete aiPlayer_;
    }
}

// NEW Setup game settings (for GUI)
void Game::setupGame(std::string player1Name, std::string player2Name, char player1Symbol, bool vsAI, AI::Difficulty difficulty)
{
    player1Name_ = player1Name;
    player2Name_ = player2Name;
    player1Symbol_ = toupper(player1Symbol);
    player2Symbol_ = (player1Symbol_ == 'X') ? 'O' : 'X';
    vsAI_ = vsAI;
    aiDifficulty_ = difficulty;

    if (vsAI_) {
        aiPlayer_ = new AI(player2Symbol_, player1Symbol_, aiDifficulty_);
    }
}

// Switch player turn
void Game::switchPlayer(std::string& currentPlayerName, char& currentPlayerSymbol) {
    if (currentPlayerName == player1Name_) {
        currentPlayerName = player2Name_;
        currentPlayerSymbol = player2Symbol_;
    }
    else {
        currentPlayerName = player1Name_;
        currentPlayerSymbol = player1Symbol_;
    }
}

// Old play() is NOT used anymore in GUI
// You don't need console play() for GUI
// You manage moves inside TicTacToeWindow instead
