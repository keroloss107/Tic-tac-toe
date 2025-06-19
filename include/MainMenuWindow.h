#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QWidget>

namespace Ui {
    class MainMenuWindow;
}

class MainMenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWindow(QString username, QWidget* parent = nullptr);
    ~MainMenuWindow();

signals:
    void startGameRequested();
    void logoutRequested();

private slots:
    void on_startGameButton_clicked();
    void on_logoutButton_clicked();
    void on_historyButton_clicked(); 

private:
    Ui::MainMenuWindow* ui;
    QString username_;
};

#endif // MAINMENUWINDOW_H
#pragma once
