#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QMessageBox>
#include "RegisterWindow.h"
#include "DatabaseManager.h"
#include "MainMenuWindow.h"

QString username;

LoginWindow::LoginWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("Login");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }

    if (DatabaseManager::instance().loginUser(username, password)) {
        MainMenuWindow* mainMenuWin = new MainMenuWindow(username);
        mainMenuWin->show();
        this->close();
    }
    else {
        QMessageBox::warning(this, "Login Failed", "Incorrect username or password.");
    }
}

void LoginWindow::on_registerButton_clicked()
{
    RegisterWindow* registerWin = new RegisterWindow();
    registerWin->show();
}
