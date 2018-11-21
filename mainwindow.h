#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

#include "chart.h"
#include "playereditdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_playerEditButton_clicked();
    void on_chartSaveButton_clicked();
    void on_actionSpeichern_triggered();
    void on_actionOeffnen_triggered();
    void on_actionExportieren_triggered();
    void on_redrawButton_clicked();
    void resizeEvent(QResizeEvent *event);
    
private:
    Ui::MainWindow *ui;
    PlayerEditDialog *playerEditDialog;
    Chart *chart;
};

#endif // MAINWINDOW_H
