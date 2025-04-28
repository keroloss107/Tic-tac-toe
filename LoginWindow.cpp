#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QMessageBox>
#include <QString>
#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"
#include "DatabaseManager.h"
#include <QFile>
#include <QCryptographicHash>
#include <QTextStream>
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

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open users file.");
        return;
    }

    QTextStream in(&file);
    QByteArray enteredPasswordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    bool loginSuccess = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() == 2) {
            QString savedUsername = parts.at(0);
            QString savedPasswordHash = parts.at(1);

            if (savedUsername == username && savedPasswordHash == enteredPasswordHash) {
                loginSuccess = true;
                break;
            }
        }
    }

    file.close();

    if (loginSuccess) {

		MainMenuWindow* mainMenuWin = new MainMenuWindow(username);
        mainMenuWin->show();
        // Open Tic Tac Toe Main Window here
         // Optionally close login window
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

void LoginWindow::tryLogin(const QString& username, const QString& password)
{
    // Dummy login logic for now
    if (username == "admin" && password == "admin") {
        QMessageBox::information(this, "Login Successful", "Welcome, admin!");
        // TODO: Open Tic Tac Toe main window
    }
    else {
        QMessageBox::critical(this, "Login Failed", "Incorrect username or password.");
    }
}
