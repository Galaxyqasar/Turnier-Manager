#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QPlainTextEdit>
#include <QScrollArea>
#include <QLayout>
#include <QImage>
#include <QPainter>
#include <QJsonDocument>
#include <QFile>

class MatchDisplay;
class ChartDisplay;
enum State{
    not_started,
    running,
    finished
};

typedef struct Player{
    QString name;
    int index;
} Player;

typedef  struct Match{
    QPair<Player, Player> players;
    QPair<int, int> scores;
    short index, layer;
    State state;
} Match;

class Chart : public QObject
{
    Q_OBJECT
public:
    explicit Chart(QObject *parent = nullptr);
    Chart(QPlainTextEdit *nameDisplay, ChartDisplay *chartDisplay, QWidget *matchScrollAreaContents, QLayout *matchScrollAreaLayout);
    QString getPlayerNames();
    void setPlayers(QString names);
    void listPlayers();
    void initMatches();
    void showRunningMatches();
    void showResults();
    QImage draw();
    int maxNameLength();
    void sortMatches();
    int getVLayer(int i, int layer);
    int maxLayer();
    int minLayer();
    int getNextPot(int min);
    void save(QString filename);
    void load(QString filename);
    bool isValid();

signals:

public slots:
    void matchFinished(QPair<int, int> score);
private:
    QList<Player> players;
    QList<Match> matches;
    ChartDisplay *chartDisplay;
    QPlainTextEdit *nameDisplay;
    QWidget *matchScrollAreaContents;
    QLayout *matchScrollAreaLayout;
    QList<MatchDisplay*> matchDisplayList;
    
    QPair<Player, Player> initPlayers();
    int getNumLayers(int numPlayers);
    Player ghost;
    Match ghostMatch;
};

#endif // CHART_H
