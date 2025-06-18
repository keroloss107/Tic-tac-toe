#ifndef GAMEHISTORYWINDOW_H
#define GAMEHISTORYWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class GameHistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameHistoryWindow(QWidget* parent = nullptr);
    void loadHistory(const QString& player);

signals:
    void backToMenu();

private slots:
    void handleBackClicked();

private:
    QLabel* historyLabel;
    QListWidget* historyListWidget;
    QPushButton* backButton;
};

#endif // GAMEHISTORYWINDOW_H
