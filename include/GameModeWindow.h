#ifndef GAMEMODEWINDOW_H
#define GAMEMODEWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GameModeWindow; }
QT_END_NAMESPACE

class GameModeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameModeWindow(QWidget* parent = nullptr);
    ~GameModeWindow();

private slots:
    void on_startButton_clicked();
    void on_pvpRadioButton_toggled(bool checked);
    void on_pvaiRadioButton_toggled(bool checked);

private:
    Ui::GameModeWindow* ui;
};

#endif // GAMEMODEWINDOW_H
#pragma once
