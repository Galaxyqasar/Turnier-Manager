#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    playerEditDialog = new PlayerEditDialog(this);
    chart = new Chart(ui->nameDisplay, ui->chartDisplay, ui->scrollAreaWidgetContents, ui->horizontalLayout_3);
    ui->chartDisplay->setChart(chart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playerEditButton_clicked()
{
    playerEditDialog->setText("a1\nb1\nc1\nd1\ne1\nf1\ng1\nh1\na2\nb2\nc2\nd2\ne2\nf2\ng2\nh2");
    playerEditDialog->exec();
    chart->setPlayers(playerEditDialog->getText());
    chart->listPlayers();
    chart->initMatches();
    chart->showRunningMatches();
}

void MainWindow::on_chartSaveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
            this,
            nullptr,
            nullptr,
            tr("PNG (*.png);;JPEG (*.jpg *.jpeg);;All files (*.*)" )
    );
    QImage img = chart->draw();
    img.save(fileName);
}

void MainWindow::on_actionSpeichern_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
            this,
            nullptr,
            nullptr,
            tr("JSON (*.json);;All files (*.*)" )
    );
    chart->save(fileName);
}

void MainWindow::on_actionOeffnen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            nullptr,
            nullptr,
            tr("JSON (*.json);;All files (*.*)" )
    );
    chart->load(fileName);
}

void MainWindow::on_actionExportieren_triggered()
{
    on_chartSaveButton_clicked();
}

void MainWindow::on_redrawButton_clicked()
{
    if(chart->isValid())
        ui->chartDisplay->drawChart();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize oldS = event->oldSize(), newS = event->size();
    if(newS.width() < 600 || newS.height() < 400)
        return;
    if(oldS.width() < newS.width() && oldS.height() < newS.height())
        if(chart->isValid())
            ui->chartDisplay->drawChart();
    qDebug()<<"resized"<<event->oldSize()<<event->size();
}
