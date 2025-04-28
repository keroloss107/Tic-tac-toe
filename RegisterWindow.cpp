#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QString>

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

    saveUserCredentials(username, password);
    QMessageBox::information(this, "Success", "Account created successfully!");
    this->close(); // Close window after successful registration
}

void RegisterWindow::saveUserCredentials(const QString& username, const QString& password)
{
    QFile file("users.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
        out << username << " " << hashedPassword << "\n";
        file.close();
    }
    else {
        QMessageBox::critical(this, "Error", "Could not open users file.");
    }
}
