#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"
#include <QMessageBox>
#include "DatabaseManager.h"

RegisterWindow::RegisterWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    setWindowTitle("Register");
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_registerButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Password Mismatch", "Passwords do not match!");
        return;
    }

    if (DatabaseManager::instance().registerUser(username, password)) {
        QMessageBox::information(this, "Success", "Account created successfully!");
        this->close();
    }
    else {
        QMessageBox::critical(this, "Error", "Registration failed. Username might already exist.");
    }
}
