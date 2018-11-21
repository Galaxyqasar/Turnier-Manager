#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QStringList args;
    for(int i = 0; i < argc; i++)
            args.append(argv[i]);
    if(args.last().contains("-V"))
        printf("Programm written by Galaxyqasar(github.com/Galaxyqasar)");
    return a.exec();
}
