#include "MainMenuWindow.h"
#include "ui_MainMenuWindow.h"
#include "GameModeWindow.h"

MainMenuWindow::MainMenuWindow(QString username, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::MainMenuWindow),
    username_(username)
{
    ui->setupUi(this);
    setWindowTitle("MainMenu");
    // Set welcome text
    ui->titleLabel->setText("Welcome, " + username_ + "!");
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}

void MainMenuWindow::on_startGameButton_clicked()
{ 
    GameModeWindow* gamemode = new GameModeWindow();
    gamemode->show();
    emit startGameRequested(); // We signal that the user wants to start a game
}

void MainMenuWindow::on_logoutButton_clicked()
{
    emit logoutRequested(); // Signal that the user wants to logout
}

void MainMenuWindow::on_historyButton_clicked()
{
    // (optional, you can implement later)
}
