#ifndef CHARTDISPLAY_H
#define CHARTDISPLAY_H

#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QSpinBox>
#include <QPaintEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

#include "chart.h"

class MatchDisplay : public QWidget{
    Q_OBJECT
public:
    MatchDisplay(QPair<Player, Player> players, int matchIndex, QWidget *parent = nullptr): QWidget (parent){
        finishButton = new QPushButton(QApplication::translate("Match Display Widget", "Beenden"), this);
        mainLayout = new QVBoxLayout(this);
        playerLabels.first = new QLabel(players.first.name, this);
        playerLabels.second = new QLabel(players.second.name, this);
        playerScoreSpinBoxes.first = new QSpinBox(this);
        playerScoreSpinBoxes.second = new QSpinBox(this);
        mainLayout->addWidget(playerLabels.first);
        mainLayout->addWidget(playerScoreSpinBoxes.first);
        mainLayout->addWidget(playerLabels.second);
        mainLayout->addWidget(playerScoreSpinBoxes.second);
        mainLayout->addWidget(finishButton);
        connect(finishButton, &QPushButton::clicked, this, [&]{
            emit this->finished(QPair<int, int> (\
                    this->playerScoreSpinBoxes.first->value(), \
                    this->playerScoreSpinBoxes.second->value()));
        });
        this->matchIndex = matchIndex;
        this->players = players;
    }
    void update(){
        if(players.second.index == -1)
            emit this->finished(QPair<int, int> (0,-1));
        else if(players.first.index == -1)
            emit this->finished(QPair<int, int> (-1,0));
    }
    ~MatchDisplay(){
        delete playerLabels.first;
        delete playerLabels.second;
        delete playerScoreSpinBoxes.first;
        delete playerScoreSpinBoxes.second;
        delete finishButton;
        delete mainLayout;
    }
    int matchIndex;
    QPair<QSpinBox*, QSpinBox*> playerScoreSpinBoxes;
private:
    QPair<QLabel*, QLabel*> playerLabels;
    QPushButton *finishButton;
    QVBoxLayout *mainLayout;
    QPair<Player, Player> players;
    
signals:
    void finished(QPair<int, int> score);
};

class Chart;

class ChartDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit ChartDisplay(QWidget *parent = nullptr);
    ~ChartDisplay();
    void setChart(Chart *chart);
    void drawChart();

signals:

public slots:
private:
    Chart *chart;
    QImage chartDisplay;
    QPainter painter;
};

#endif // CHARTDISPLAY_H
