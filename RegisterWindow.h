#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWindow; }
QT_END_NAMESPACE

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget* parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_registerButton_clicked();

private:
    Ui::RegisterWindow* ui;
    void saveUserCredentials(const QString& username, const QString& password);
};

#endif // REGISTERWINDOW_H
#pragma once
