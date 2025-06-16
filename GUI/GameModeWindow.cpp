#include "GameModeWindow.h"
#include "ui_GameModeWindow.h"
#include "TicTacToe.h"
#include "AI.h"
#include <QMessageBox>
#include <QInputDialog>

GameModeWindow::GameModeWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::GameModeWindow)
{
    ui->setupUi(this);
    ui->difficultyComboBox->addItems({ "Easy", "Medium", "Hard" });
    ui->difficultyLabel->setVisible(false);
    ui->difficultyComboBox->setVisible(false);
}

GameModeWindow::~GameModeWindow()
{
    delete ui;
}

void GameModeWindow::on_pvpRadioButton_toggled(bool checked)
{
    if (checked) {
        ui->difficultyLabel->setVisible(false);
        ui->difficultyComboBox->setVisible(false);
    }
}

void GameModeWindow::on_pvaiRadioButton_toggled(bool checked)
{
    if (checked) {
        ui->difficultyLabel->setVisible(true);
        ui->difficultyComboBox->setVisible(true);
    }
}



void GameModeWindow::on_startButton_clicked()
{
    TicTacToeWindow* gameWindow = new TicTacToeWindow();

        if (ui->pvpRadioButton->isChecked()) {
            bool ok;
            QString player2Name = QInputDialog::getText(this, tr("Player 2 Name"),
                tr("Enter Player 2 Name:"), QLineEdit::Normal,
                "", &ok);
            if (!ok || player2Name.isEmpty()) {
                player2Name = "Player2";
            }

            gameWindow->setupGame("Player1", player2Name.toStdString(), 'X', false);
        }

    else if (ui->pvaiRadioButton->isChecked()) {
        // Player vs AI
        QString diffText = ui->difficultyComboBox->currentText();
        AI::Difficulty difficulty = AI::EASY;

        if (diffText == "Medium") {
            difficulty = AI::MEDIUM;
        }
        else if (diffText == "Hard") {
            difficulty = AI::HARD;
        }

        gameWindow->setupGame("Player1", "Computer", 'X', true, difficulty);
    }

    gameWindow->show();
    this->close();
}

