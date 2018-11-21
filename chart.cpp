#include "chart.h"
#include "chartdisplay.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

Chart::Chart(QObject *parent) : QObject(parent)
{
    
}

Chart::Chart(QPlainTextEdit *nameDisplay, ChartDisplay *chartDisplay, QWidget *matchScrollAreaContents, QLayout *matchScrollAreaLayout)
{
    this->nameDisplay = nameDisplay;
    this->chartDisplay = chartDisplay;
    this->matchScrollAreaContents = matchScrollAreaContents;
    this->matchScrollAreaLayout = matchScrollAreaLayout;
}

QString Chart::getPlayerNames()
{
    QString names = "";
    for(int i = 0; i < players.length(); i++)
        names += players[i].name +"\n";
    return names;
}

void Chart::setPlayers(QString names)
{
    QStringList players = names.split("\n");
    this->players.clear();
    for(int i = 0; i < players.length(); i++){
        if(players[i] == "")
            break;
        Player player;
        player.index = i+1;
        player.name = players[i];
        this->players.append(player);
    }
}

void Chart::listPlayers()
{
    QString text = "";
    for(int i = 0; i < players.length(); i++)
        text += QString::number(players[i].index) + ".   " + players[i].name + "\n";
    nameDisplay->setPlainText(text);
}

void Chart::initMatches()
{
    qDebug()<<"init: 1";
    matches.clear();
    short layer = 0;
    ghost.index = 0;
    ghost.name = " ";
    int newCount = getNextPot(players.length());
    while(players.length() < newCount)
        players.append(ghost);  
    short globalindex = 0;
    for(short i = 0; i < players.length()/2; i++){
        Match match;
        match.index = globalindex++;
        match.players = QPair<Player, Player>(players[2*i], players[2*i+1]);
        match.layer = layer;
        match.state = running;
        match.scores = QPair<int, int>(0,0);
        matches.append(match);
    }
    qDebug()<<matches.length();
    
    Match match;
    match.state = not_started;
    match.scores = QPair<int, int>(0,0);
    match.players = initPlayers();
    
    int numLayers = getNumLayers(players.length());
    int nextPlayers = (players.length()+1)/2;
    for(short i = 1; i < numLayers; i++){
        match.layer = i;
        nextPlayers = (nextPlayers+1)/2;
        for(int k = 0; k < nextPlayers; k++){
            match.layer =  1*i +0;
            match.index = globalindex++;
            matches.append(match);
            match.layer = -2*i +1;
            match.index = globalindex++;
            matches.append(match);
            match.layer = -2*i +0;
            match.index = globalindex++;
            matches.append(match);
        }
    }
    
    Match finale;
    finale.layer = SHRT_MAX;
    finale.state = not_started;
    finale.scores = QPair<int, int>(0,0);
    finale.players = initPlayers();
    finale.index = globalindex;
    matches.append(finale);
    
    qDebug()<<matches.length()<<newCount;
}

void Chart::showRunningMatches()
{
    MatchDisplay *tmp;
    while(!matchDisplayList.isEmpty() && (tmp = matchDisplayList.takeFirst()) != nullptr){
        matchScrollAreaLayout->removeWidget(tmp);
        delete tmp;
    }
    matchDisplayList.clear();
    for(int i = 0; i < matches.length(); i++){
        if(matches[i].state == running){
            matchDisplayList.append(new MatchDisplay(matches[i].players, i, matchScrollAreaContents));
            matchDisplayList.last()->playerScoreSpinBoxes.first->setValue(1);
            matchScrollAreaLayout->addWidget(matchDisplayList.last());
            connect(matchDisplayList.last(), SIGNAL(finished(QPair<int, int>)), this, SLOT(matchFinished(QPair<int, int>)));
            matchDisplayList.last()->update();
        }
        qDebug()<<matches[i].players.first.name<<matches[i].players.second.name<<matches[i].layer<<matches[i].scores<<matches[i].state;
    }
    chartDisplay->drawChart();
}

void Chart::showResults()
{
    for(int i = 0; i < matches.length(); i++){
        Match match = matches[i];
        qDebug()<<match.index<<match.layer<<match.players.first.name<<match.players.second.name;
    }
}

QImage Chart::draw()
{
    int l_width = chartDisplay->width(), l_height = chartDisplay->height();
    int width, height;
    double xScale, yScale;
    qDebug()<<maxNameLength();
    const int matchWidth = maxNameLength()*10+20, matchHeight = 30, hdiff = 30, vdiff = 10, hborder = 50, vborder = 50;
    int playerCount = 0;
    for(int i = 0; i < players.length(); i++)
        playerCount += (players[i].index == -1) ? 0 : 1;
    height = (playerCount/2)*(matchHeight+vdiff)+2*vborder + matchHeight;
    width = getNumLayers(players.length())*3*(matchWidth + hdiff)+hborder;
    xScale = double(l_width)/double(width);
    yScale = double(l_height)/double(height);
    xScale = xScale < 1.0 ? 1.0 : xScale;
    yScale = yScale < 1.0 ? 1.0 : yScale;
    qDebug()<<xScale<<l_width<<width;
    qDebug()<<yScale<<l_height<<height;
    QImage result(int(double(width)*xScale), int(double(height)*yScale), QImage::Format_RGB888);
    result.fill(Qt::white);
    QPainter painter(&result);
    QFont std = painter.font();
    std.setPixelSize(12*int((xScale < yScale)? xScale : yScale));
    painter.setFont(std);
    painter.drawRect(int(double(vborder)/2*xScale), int(double(hborder)/2*yScale), 
                     int(double(width-vborder)*xScale), int(double(height-hborder)*yScale));
    for(int i = 0; i < matches.length(); i++){
        Match current = matches[i];
        if(current.players.first.index == -1 || current.players.second.index == -1)
            continue;
        short layer = current.layer;
        if(layer == SHRT_MAX)
            layer = short(getNumLayers(players.length()));
        int m_vlayer = getVLayer(i, layer);
        int m_hpos = width/2 + layer * (matchWidth + hdiff) + hborder, 
                m_vpos = m_vlayer * (matchHeight+vdiff) + vborder;
        QRect rect = QRect(int(double(m_hpos)*xScale), int(double(m_vpos)*yScale), 
                           int(double(matchWidth)*xScale), int(double(matchHeight)*yScale));
        if(current.state == running)
            painter.fillRect(rect, QBrush(Qt::green));
        else if(current.state == finished)
            painter.fillRect(rect, QBrush(QColor(Qt::red).lighter()));
        painter.drawRect(rect);
        rect.setX(rect.x()+3);
        rect.setWidth(rect.width()-3);
        painter.drawText(rect, QString(matches[i].players.first.name + " : " + QString::number(matches[i].scores.first) + "\n" +
                                       matches[i].players.second.name + " : " + QString::number(matches[i].scores.second)));
    }
    if(matches.last().state == finished){
        QString msg = QString(tr("Der Gewinner ist : ") + matches.last().players.first.name + " !");
        QFont old, tmp;
        old = tmp = painter.font();
        tmp.setPixelSize(24*int((xScale < yScale)? xScale : yScale));
        tmp.setBold(true);
        tmp.setUnderline(true);
        painter.setFont(tmp);
        int x = width/2 + minLayer() * (matchWidth + hdiff) + hborder;
        int y = (playerCount/2 - 1) * (matchHeight+vdiff) + vborder;
        QRect rect = QRect(x, y-35, msg.length()*12+5, 50);
        painter.fillRect(rect, QBrush(QColor(Qt::green).lighter()));
        painter.drawRect(rect);
        painter.drawText(x + 5, y, msg);
        painter.setFont(old);
    }
    painter.end();
    return result;
}

int Chart::maxNameLength()
{
    int maxLength = 0;
    for(int i = 0; i < players.length(); i++){
        if(players[i].name.length() > maxLength)
            maxLength = players[i].name.length();
    }
    return maxLength;
}

void Chart::sortMatches()
{
    QList<Match> newMatches;
    newMatches.reserve(matches.length());
    newMatches.append(matches.first());
    qDebug()<<"1"<<newMatches.first().layer;
    for(int i = 1; i < matches.length(); i++){
        qDebug()<<"2";
        Match current = matches[i];
        if(abs(current.layer)>=abs(newMatches[i-1].layer) && current.layer >= newMatches[i-1].layer){
            newMatches.append(current);
        }
        else{
            for(int k = 0; k < newMatches.length(); k++){
                if(abs(current.layer)>=abs(newMatches[k].layer) && current.layer >= newMatches[k].layer){
                    newMatches.insert(k-1, current);
                    break;
                }
            }
        }
    }
    qDebug()<<"3";
    for(short i = 0; i < newMatches.length(); i++)
        newMatches[i].index = i;
    matches = newMatches;
}

int Chart::getVLayer(int i, int layer)
{
    int count = 0;
    for(int k = 0; k < i; k++){
        if(matches[k].layer == layer && !(matches[k].players.first.index == -1 || matches[k].players.second.index == -1))
            count ++;
    }
    return count;
}

int Chart::maxLayer()
{
    int max = 0;
    for(int i = 0; i < matches.length()-1; i++)
        if(matches[i].layer > max)
            max = matches[i].layer;
    return max;
}

int Chart::minLayer()
{
    int min = 0;
    for(int i = 0; i < matches.length(); i++)
        if(matches[i].layer < min)
            min = matches[i].layer;
    return min;
}

int Chart::getNextPot(int min)
{
    for(int i = 1; i < 10000; i <<=1){
        if(i >= min)
            return i;
    }
    return 0;
}

void Chart::save(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QJsonDocument doc;
    QJsonObject mainObject;
    QJsonArray playerArray, matchArray;
    for(int i = 0; i < players.length(); i++){
        QString name = players[i].name;
        int index = players[i].index;
        QJsonObject player;
        player.insert("name", QJsonValue(name));
        player.insert("index", QJsonValue(index));
        playerArray.push_back(player);
    }
    mainObject.insert("Players", playerArray);
    for(int i = 0; i < matches.length(); i++){
        Match tmp = matches[i];
        int index = tmp.index;
        int layer = tmp.layer;
        QPair<Player, Player> players = tmp.players;
        QPair<int, int> scores = tmp.scores;
        int state = tmp.state;
        QJsonObject match, firstPlayer, secondPlayer;
        QJsonArray playerPair, scorePair;
        firstPlayer.insert("name", players.first.name);
        firstPlayer.insert("index", players.first.index);
        secondPlayer.insert("name", players.second.name);
        secondPlayer.insert("index", players.second.index);
        playerPair.push_back(firstPlayer);
        playerPair.push_back(secondPlayer);
        scorePair.push_back(QJsonValue(scores.first));
        scorePair.push_back(QJsonValue(scores.second));
        match.insert("index", index);
        match.insert("layer", layer);
        match.insert("players", playerPair);
        match.insert("score", scorePair);
        match.insert("state", state);
        matchArray.push_back(match);
    }
    mainObject.insert("Matches", QJsonValue(matchArray));
    doc.setObject(mainObject);    
    QByteArray data = doc.toJson();    
    file.write(data);
    file.close();
}

void Chart::load(QString filename)
{
    players.clear();
    matches.clear();
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject mainObject = doc.object();
    QJsonArray playerArray = mainObject.take("Players").toArray();
    QJsonArray matchArray = mainObject.take("Matches").toArray();
    qDebug()<<playerArray.count()<<playerArray.count();
    foreach(const QJsonValue & value, playerArray){
        QJsonObject player = value.toObject();
        Player tmp;
        tmp.name = player.take("name").toString();
        tmp.index = player.take("index").toInt();
        players.append(tmp);
    }
    foreach(const QJsonValue & value, matchArray){
        QJsonObject match = value.toObject();
        QJsonArray players = match.take("players").toArray();
        QJsonArray scores = match.take("score").toArray();
        if(players.count() != 2 || scores.count() != 2)
            qDebug()<<"error"<<players.count();
        Player player1, player2;
        player1.name = players.first().toObject().take("name").toString();
        player2.name = players.last().toObject().take("name").toString();
        player1.index = players.first().toObject().take("index").toInt();
        player2.index = players.last().toObject().take("index").toInt();
        Match tmp;
        tmp.index = short(match.take("index").toInt());
        tmp.layer = short(match.take("layer").toInt());
        tmp.players = QPair<Player, Player>(player1, player2);
        tmp.scores = QPair<int, int>(scores.first().toInt(),scores.last().toInt());
        tmp.state = State(match.take("state").toInt());
        matches.append(tmp);
    }
    qDebug()<<players.size()<<matches.size();
    for(int i = 0; i < players.size(); i++)
        qDebug()<<players[i].name;
    showRunningMatches();
    listPlayers();
}

bool Chart::isValid()
{
    if(players.size() < 2)
        return false;
    if(matches.size() < 1)
        return false;
    return true;
}

void Chart::matchFinished(QPair<int, int> score)
{
    int index = matchDisplayList.indexOf(qobject_cast<MatchDisplay*>(sender()));
    int matchIndex = matchDisplayList[index]->matchIndex;
    matchScrollAreaLayout->removeWidget(matchDisplayList[index]);
    delete matchDisplayList[index];
    matchDisplayList.removeAt(index);
    
    if(score.first < score.second){
        matches[matchIndex].players = QPair<Player, Player>(matches[matchIndex].players.second, matches[matchIndex].players.first);
        score = QPair<int, int>(score.second, score.first);
    }
    
    Player winner = matches[matchIndex].players.first, looser = matches[matchIndex].players.second;
    
    qDebug()<<"Winner: "<<winner.name<<"\t\tLooser: "<<looser.name;
    
    int layer = matches[matchIndex].layer;
    if(layer == SHRT_MAX){
        matches[matchIndex].scores = score;
        matches[matchIndex].state = finished;
        qDebug()<<score<<matchIndex;
        showRunningMatches();
        return;
    }
    int newLayerW = (layer >= 0)? layer + 1 : layer - 1;
    int newLayerL = (layer > 0)? (layer * - 2) : ((layer == 0)? -1 : 0);
    if(layer == maxLayer())
        matches.last().players.first = winner;
    if(layer == minLayer())
        matches.last().players.second = winner;
    if((matches.last().players.first.index != -2) && (matches.last().players.second.index != -2))
        matches.last().state = running;
    for(int i = 0; i < matches.length(); i++){
        if(matches[i].layer == newLayerW){
            if(matches[i].players.first.index == -2){
                matches[i].players.first = winner;
                if(winner.index == -1){
                    matches[i].scores = QPair<int, int>(-1, 0);
                }            
                break;
            }
            else if(matches[i].players.second.index == -2){
                matches[i].players.second = winner;
                matches[i].state = running;
                if(winner.index == -1){
                    matches[i].scores = QPair<int, int>(0, -1);
                }                    
                break;
            }
        }
    }
    if(newLayerL != 0){
        for(int i = 0; i < matches.length(); i++){
            if(matches[i].layer == newLayerL){
                if(matches[i].players.first.index == -2){
                    matches[i].players.first = looser;
                    if(winner.index == -1){
                        matches[i].scores = QPair<int, int>(-1, 0);
                    }            
                    break;
                }
                else if(matches[i].players.second.index == -2){
                    matches[i].players.second = looser;
                    matches[i].state = running;
                    if(winner.index == -1){
                        matches[i].scores = QPair<int, int>(0, -1);
                    }            
                    break;
                }
            }
        }
    }    
    matches[matchIndex].scores = score;
    matches[matchIndex].state = finished;
    qDebug()<<score<<matchIndex;
    showRunningMatches();
}

QPair<Player, Player> Chart::initPlayers()
{
    Player player;
    player.index = -2;
    player.name = "_";
    return QPair<Player, Player>(player, player);
}

int Chart::getNumLayers(int numPlayers)
{
    int numLayers = 0;
    while(numPlayers > 1){
        if(numPlayers %2 == 1)
            numPlayers += 1;
        numPlayers /= 2;
        numLayers += 1;
    }
    return numLayers;
}
