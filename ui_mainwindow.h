/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "chartdisplay.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOeffnen;
    QAction *actionSpeichern;
    QAction *actionExportieren;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *playerEditButton;
    QPushButton *chartSaveButton;
    QPushButton *redrawButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *tableHBoxLayout;
    QPlainTextEdit *nameDisplay;
    QScrollArea *chartScrollArea;
    QWidget *chartScrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    ChartDisplay *chartDisplay;
    QScrollArea *matchScrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_3;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1200, 800);
        MainWindow->setMinimumSize(600, 400);
        actionOeffnen = new QAction(MainWindow);
        actionOeffnen->setObjectName(QStringLiteral("actionOeffnen"));
        actionSpeichern = new QAction(MainWindow);
        actionSpeichern->setObjectName(QStringLiteral("actionSpeichern"));
        actionExportieren = new QAction(MainWindow);
        actionExportieren->setObjectName(QStringLiteral("actionExportieren"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        playerEditButton = new QPushButton(centralWidget);
        playerEditButton->setObjectName(QStringLiteral("playerEditButton"));
        chartSaveButton = new QPushButton(centralWidget);
        chartSaveButton->setObjectName(QStringLiteral("chartSaveButton"));
        redrawButton = new QPushButton(centralWidget);
        redrawButton->setObjectName(QStringLiteral("redrawButton"));
        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout_2->addWidget(playerEditButton);
        horizontalLayout_2->addWidget(chartSaveButton);
        horizontalLayout_2->addWidget(redrawButton);
        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout->addLayout(horizontalLayout_2);

        tableHBoxLayout = new QHBoxLayout();
        tableHBoxLayout->setSpacing(6);
        tableHBoxLayout->setObjectName(QStringLiteral("tableHBoxLayout"));
        nameDisplay = new QPlainTextEdit(centralWidget);
        nameDisplay->setObjectName(QStringLiteral("nameDisplay"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nameDisplay->sizePolicy().hasHeightForWidth());
        nameDisplay->setSizePolicy(sizePolicy);
        nameDisplay->setReadOnly(true);

        tableHBoxLayout->addWidget(nameDisplay);

        chartScrollArea = new QScrollArea(centralWidget);
        chartScrollArea->setObjectName(QStringLiteral("chartScrollArea"));
        chartScrollArea->setWidgetResizable(true);
        chartScrollAreaWidgetContents = new QWidget();
        chartScrollAreaWidgetContents->setObjectName(QStringLiteral("chartScrollAreaWidgetContents"));
        chartScrollAreaWidgetContents->setGeometry(QRect(0, 0, 854, 483));
        verticalLayout_2 = new QVBoxLayout(chartScrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        chartDisplay = new ChartDisplay(chartScrollAreaWidgetContents);
        chartDisplay->setObjectName(QStringLiteral("chartDisplay"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(chartDisplay->sizePolicy().hasHeightForWidth());
        chartDisplay->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(chartDisplay);

        chartScrollArea->setWidget(chartScrollAreaWidgetContents);

        tableHBoxLayout->addWidget(chartScrollArea);


        verticalLayout->addLayout(tableHBoxLayout);

        matchScrollArea = new QScrollArea(centralWidget);
        matchScrollArea->setObjectName(QStringLiteral("matchScrollArea"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(matchScrollArea->sizePolicy().hasHeightForWidth());
        matchScrollArea->setSizePolicy(sizePolicy2);
        matchScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        matchScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        matchScrollArea->setWidgetResizable(true);
        matchScrollArea->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        matchScrollArea->setMinimumHeight(175);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1118, 54));
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 0));
        horizontalLayout_3 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        matchScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(matchScrollArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1138, 20));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuDatei->addAction(actionOeffnen);
        menuDatei->addAction(actionSpeichern);
        menuDatei->addAction(actionExportieren);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Turnier Manager", nullptr));
        actionOeffnen->setText(QApplication::translate("MainWindow", "\303\226ffnen", nullptr));
        actionSpeichern->setText(QApplication::translate("MainWindow", "Speichern", nullptr));
        actionExportieren->setText(QApplication::translate("MainWindow", "Exportieren", nullptr));
        playerEditButton->setText(QApplication::translate("MainWindow", "Spieler Bearbeiten", nullptr));
        chartSaveButton->setText(QApplication::translate("MainWindow", "Diagramm speichern", nullptr));
        redrawButton->setText(QApplication::translate("MainWindow", "Diagramm neu zeichnen", nullptr));
        nameDisplay->setPlainText(QApplication::translate("MainWindow", "", nullptr));
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
