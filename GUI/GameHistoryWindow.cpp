#include "GameHistoryWindow.h"
#include "DatabaseManager.h"

#include <QVariantMap>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

extern QString username;

GameHistoryWindow::GameHistoryWindow(QWidget* parent)
    : QWidget(parent)
{
    historyLabel = new QLabel("Game History");
    historyLabel->setAlignment(Qt::AlignHCenter);
    historyLabel->setStyleSheet("font-weight: bold; font-size: 18px;");

    historyListWidget = new QListWidget(this);
    backButton = new QPushButton("Back to Menu", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(historyLabel);
    layout->addWidget(historyListWidget);
    layout->addWidget(backButton);

    setLayout(layout);

    connect(backButton, &QPushButton::clicked, this, &GameHistoryWindow::handleBackClicked);
}

void GameHistoryWindow::loadHistory(const QString& player)
{
    historyListWidget->clear();

    QList<QVariantMap> history = DatabaseManager::instance().getGameHistory(player);

    if (history.isEmpty()) {
        historyListWidget->addItem("No game history found.");
        return;
    }

    int wins = 0;
    int losses = 0;
    int draws = 0;

    for (const QVariantMap& entry : history) {
        QString result = entry["result"].toString();
        QString opponent = entry["opponent"].toString();
        QString date = entry["date"].toString();

        if (result == (username + " wins")) wins++;
        else if (result == (username + " lost")) losses++;
        else if (result == "Draw") draws++;

        QString line = QString("[%1] Result: %2 vs %3").arg(date, result, opponent);
        historyListWidget->addItem(line);
    }

    QString summary = QString("Total - Wins: %1 | Losses: %2 | Draws: %3").arg(wins).arg(losses).arg(draws);
    historyListWidget->insertItem(0, summary);
}

void GameHistoryWindow::handleBackClicked()
{
	this->close(); 
}
