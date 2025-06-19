#include "TicTacToe.h"
#include "ui_TicTacToe.h"
#include <QMessageBox>
#include "GameModeWindow.h"
#include "MainMenuWindow.h"
#include "LoginWindow.h"
#include "DatabaseManager.h"

TicTacToeWindow::TicTacToeWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToeWindow)
    , gameOver_(false)
{
    ui->setupUi(this);
    setupBoardButtons();
}

TicTacToeWindow::~TicTacToeWindow()
{
    delete ui;
}

void TicTacToeWindow::setupBoardButtons()
{
    boardButtons_ = {
        ui->pushButton_1, ui->pushButton_2, ui->pushButton_3,
        ui->pushButton_4, ui->pushButton_5, ui->pushButton_6,
        ui->pushButton_7, ui->pushButton_8, ui->pushButton_9
    };

    for (QPushButton* button : boardButtons_) {
        connect(button, &QPushButton::clicked, this, &TicTacToeWindow::handleButtonClick);
        button->setStyleSheet("background-color: white; font-weight: bold; font-size: 24px; color: black; border: 2px solid gray;");

    }
}

void TicTacToeWindow::setupGame(std::string player1Name, std::string player2Name, char player1Symbol, bool vsAI, AI::Difficulty difficulty)
{
    game_.setupGame(player1Name, player2Name, player1Symbol, vsAI, difficulty);
    currentPlayerName_ = player1Name;
    currentPlayerSymbol_ = player1Symbol;
    vsAI_ = vsAI;
    updateBoard();
	updateStatusLabel();
}

void TicTacToeWindow::handleButtonClick()
{
    QElapsedTimer clickTimer;
    clickTimer.start();

    // ... original button click logic here ...


    if (gameOver_) return;

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    int index = boardButtons_.indexOf(clickedButton);

    int row = index / 3;
    int col = index % 3;

    if (!game_.getBoard().isCellEmpty(row, col)) {
        return;
    }

    game_.getBoard().makeMove(row, col, currentPlayerSymbol_);
    updateBoard();
    checkGameOver();

    switchPlayer();
    updateStatusLabel();


    if (vsAI_ && currentPlayerName_ == "Computer" && !gameOver_) {
        aiMove();
        updateBoard();
        checkGameOver();
        switchPlayer();
        updateStatusLabel();

    }
    qDebug() << "[PERF] Button click processed in" << clickTimer.elapsed() << "ms";

}

void TicTacToeWindow::updateBoard()
{
    const Board& board = game_.getBoard();
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            char mark = board.getCell(row, col);
            int index = row * 3 + col;

            if (mark == 'X') {
                boardButtons_[index]->setText("X");
                boardButtons_[index]->setStyleSheet(
                    "color: #ff4d6d; background-color: #1f4068; border: 2px solid #00d4ff; "
                    "font-size: 40px; font-weight: bold; border-radius: 12px;");
            }
            else if (mark == 'O') {
                boardButtons_[index]->setText("O");
                boardButtons_[index]->setStyleSheet(
                    "color: #00d4ff; background-color: #1f4068; border: 2px solid #00d4ff; "
                    "font-size: 40px; font-weight: bold; border-radius: 12px;");
            }
            else {
                boardButtons_[index]->setText("");
                boardButtons_[index]->setStyleSheet(
                    "color: white; background-color: #1f4068; border: 2px solid #00d4ff; "
                    "font-size: 40px; font-weight: bold; border-radius: 12px;");
            }
        }
    }
}


void TicTacToeWindow::checkGameOver()
{
    int result = game_.getBoard().evaluate();
    bool movesLeft = game_.getBoard().isMovesLeft();

    extern QString username;

    QString resultText;
    QString opponentName = (username == QString::fromStdString(game_.getPlayer1Name()))
        ? QString::fromStdString(game_.getPlayer2Name())
        : QString::fromStdString(game_.getPlayer1Name());

    if ((result == 10 && currentPlayerSymbol_ == game_.getPlayer2Symbol()) ||
        (result == -10 && currentPlayerSymbol_ == game_.getPlayer1Symbol()))
    {
        if (currentPlayerName_ == game_.getPlayer1Name()) {
            resultText = username + " wins";
        }
        else {
            resultText = username + " lost";
        }

        DatabaseManager::instance().saveGameResult(username, opponentName, resultText);

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Game Over", resultText + "\n\nPlay Again?",
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            this->close();
            GameModeWindow* gameMode = new GameModeWindow();
            gameMode->show();
        }
        else {
            this->close();
            MainMenuWindow* mainMenu = new MainMenuWindow(username);
            mainMenu->show();
        }

        gameOver_ = true;
    }
    else if (!movesLeft)
    {
        resultText = "Draw";
        DatabaseManager::instance().saveGameResult(username, opponentName, resultText);

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Game Over", "It's a Draw!\n\nPlay Again?",
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            this->close();
            GameModeWindow* gameMode = new GameModeWindow();
            gameMode->show();
        }
        else {
            this->close();
            MainMenuWindow* mainMenu = new MainMenuWindow(username);
            mainMenu->show();
        }

        gameOver_ = true;
    }
}


void TicTacToeWindow::switchPlayer()
{
    if (currentPlayerName_ == game_.getPlayer1Name()) {
        currentPlayerName_ = game_.getPlayer2Name();
        currentPlayerSymbol_ = game_.getPlayer2Symbol();
    }
    else {
        currentPlayerName_ = game_.getPlayer1Name();
        currentPlayerSymbol_ = game_.getPlayer1Symbol();
    }
}


void TicTacToeWindow::aiMove()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::pair<int, int> bestMove = game_.getAI()->findBestMove(game_.getBoard());

    if (bestMove.first != -1 && bestMove.second != -1) {
        game_.getBoard().makeMove(bestMove.first, bestMove.second, currentPlayerSymbol_);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    qDebug() << "[PERF] AI move took:" << duration.count() << "μs";
}

void TicTacToeWindow::disableAllButtons()
{
    for (QPushButton* button : boardButtons_) {
        button->setEnabled(false);
    }
}
void TicTacToeWindow::updateStatusLabel()
{
    QString label = QString::fromStdString(currentPlayerName_) + "'s Turn (" + currentPlayerSymbol_ + ")";
    ui->titleLabel->setText(label);
}            