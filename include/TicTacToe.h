#ifndef TICTACTOEWINDOW_H
#define TICTACTOEWINDOW_H


#include <QMainWindow>
#include <QPushButton>
#include "Game_gui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TicTacToeWindow; }
QT_END_NAMESPACE

class TicTacToeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicTacToeWindow(QWidget* parent = nullptr);
    ~TicTacToeWindow();

    void setupGame(std::string player1Name, std::string player2Name, char player1Symbol, bool vsAI, AI::Difficulty difficulty = AI::EASY);
    void updateStatusLabel();


private slots:
    void handleButtonClick();
    void updateBoard();
    void checkGameOver();
    void switchPlayer();
    void aiMove();

private:
    Ui::TicTacToeWindow* ui;
    QVector<QPushButton*> boardButtons_;
    Game game_;
    std::string currentPlayerName_;
    char currentPlayerSymbol_;
    bool vsAI_;
    bool gameOver_;
    void setupBoardButtons();
    void disableAllButtons();
};
#endif // TICTACTOEWINDOW_H

