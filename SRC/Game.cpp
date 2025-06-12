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

// Setup game settings
void Game::setupGame() {
    cout << "==============================\n";
    cout << " Welcome to Advanced Tic Tac Toe!\n";
    cout << "==============================\n\n";

    int gameMode;
    cout << "Choose Game Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs AI\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> gameMode;

    while (gameMode != 1 && gameMode != 2) {
        cout << "Invalid choice! Please enter 1 or 2: ";
        cin >> gameMode;
    }

    cin.ignore();
    cout << "Enter Player 1 name: ";
    getline(cin, player1Name_);

    if (gameMode == 1) {
        cout << "Enter Player 2 name: ";
        getline(cin, player2Name_);
    } else {
        vsAI_ = true;
        player2Name_ = "Computer";

        int difficultyChoice;
        cout << "Choose AI Difficulty:\n";
        cout << "1. Easy\n";
        cout << "2. Medium\n";
        cout << "3. Hard\n";
        cout << "Enter your choice (1-3): ";
        cin >> difficultyChoice;

        while (difficultyChoice < 1 || difficultyChoice > 3) {
            cout << "Invalid choice! Please enter 1, 2 or 3: ";
            cin >> difficultyChoice;
        }

        aiDifficulty_ = (difficultyChoice == 1) ? AI::EASY :
                        (difficultyChoice == 2) ? AI::MEDIUM : AI::HARD;
    }

    cout << player1Name_ << ", choose your symbol (X or O): ";
    cin >> player1Symbol_;
    player1Symbol_ = toupper(player1Symbol_);

    while (player1Symbol_ != 'X' && player1Symbol_ != 'O') {
        cout << "Invalid symbol! Please choose X or O: ";
        cin >> player1Symbol_;
        player1Symbol_ = toupper(player1Symbol_);
    }

    player2Symbol_ = (player1Symbol_ == 'X') ? 'O' : 'X';

    cout << player1Name_ << " will play as '" << player1Symbol_ << "'.\n";
    cout << player2Name_ << " will play as '" << player2Symbol_ << "'.\n";

    if (vsAI_) {
        aiPlayer_ = new AI(player2Symbol_, player1Symbol_, aiDifficulty_);
    }
}

// Switch player turn
void Game::switchPlayer(string& currentPlayerName, char& currentPlayerSymbol) {
    if (currentPlayerName == player1Name_) {
        currentPlayerName = player2Name_;
        currentPlayerSymbol = player2Symbol_;
    } else {
        currentPlayerName = player1Name_;
        currentPlayerSymbol = player1Symbol_;
    }
}

// Play the game
void Game::play() {
    setupGame();

    string currentPlayerName = player1Name_;
    char currentPlayerSymbol = player1Symbol_;
    bool gameOver = false;

    while (!gameOver) {
        board_.display();
        int move;

        if (currentPlayerName == "Computer") {
            cout << "Computer is thinking...\n";
            pair<int, int> bestMove = aiPlayer_->findBestMove(board_);
            board_.makeMove(bestMove.first, bestMove.second, currentPlayerSymbol);
        } else {
            cout << currentPlayerName << " (" << currentPlayerSymbol << "), enter your move (1-9): ";
            cin >> move;

            if (move < 1 || move > 9) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            if (!board_.isCellEmpty(row, col)) {
                cout << "Spot already taken! Try again.\n";
                continue;
            }

            board_.makeMove(row, col, currentPlayerSymbol);
        }

        int result = board_.evaluate();
        if ((result == 10 && currentPlayerSymbol == player2Symbol_) ||
            (result == -10 && currentPlayerSymbol == player1Symbol_)) {
            board_.display();
            cout << "Congratulations " << currentPlayerName << "! You win!\n";
            gameOver = true;
        }
        else if (!board_.isMovesLeft()) {
            board_.display();
            cout << "It's a draw!\n";
            gameOver = true;
        }
        else {
            switchPlayer(currentPlayerName, currentPlayerSymbol);
        }
    }
}

void Game::setPlayerNamesAndSymbols(const std::string& p1, const std::string& p2, char s1, char s2) {
    player1Name_ = p1;
    player2Name_ = p2;
    player1Symbol_ = s1;
    player2Symbol_ = s2;
}
// End of Game.cpp
// This file contains the implementation of the Game class and its methods.