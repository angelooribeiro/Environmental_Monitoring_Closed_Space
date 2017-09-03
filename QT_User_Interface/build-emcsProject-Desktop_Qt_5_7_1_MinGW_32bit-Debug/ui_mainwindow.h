/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pb_logo;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_client;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lb_status;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_ChangePrm;
    QPushButton *pbReads;
    QPushButton *pb_alerts;
    QPushButton *pbShutdown;
    QLabel *lb_xbee;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(200, 390);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pb_logo = new QPushButton(centralWidget);
        pb_logo->setObjectName(QStringLiteral("pb_logo"));
        pb_logo->setEnabled(true);
        pb_logo->setGeometry(QRect(40, 10, 119, 143));
        pb_logo->setStyleSheet(QStringLiteral(""));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 162, 171, 189));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lb_client = new QLabel(layoutWidget);
        lb_client->setObjectName(QStringLiteral("lb_client"));

        horizontalLayout->addWidget(lb_client);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lb_status = new QLabel(layoutWidget);
        lb_status->setObjectName(QStringLiteral("lb_status"));

        horizontalLayout_2->addWidget(lb_status);

        horizontalSpacer_7 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pb_ChangePrm = new QPushButton(layoutWidget);
        pb_ChangePrm->setObjectName(QStringLiteral("pb_ChangePrm"));

        verticalLayout->addWidget(pb_ChangePrm);

        pbReads = new QPushButton(layoutWidget);
        pbReads->setObjectName(QStringLiteral("pbReads"));

        verticalLayout->addWidget(pbReads);


        gridLayout->addLayout(verticalLayout, 5, 0, 1, 1);

        pb_alerts = new QPushButton(layoutWidget);
        pb_alerts->setObjectName(QStringLiteral("pb_alerts"));

        gridLayout->addWidget(pb_alerts, 4, 0, 1, 1);

        pbShutdown = new QPushButton(layoutWidget);
        pbShutdown->setObjectName(QStringLiteral("pbShutdown"));

        gridLayout->addWidget(pbShutdown, 3, 0, 1, 1);

        lb_xbee = new QLabel(layoutWidget);
        lb_xbee->setObjectName(QStringLiteral("lb_xbee"));

        gridLayout->addWidget(lb_xbee, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        pb_logo->raise();
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pb_logo->setText(QString());
        lb_client->setText(QApplication::translate("MainWindow", "Listening to port 1234...", Q_NULLPTR));
        lb_status->setText(QApplication::translate("MainWindow", "Click to create server", Q_NULLPTR));
        pb_ChangePrm->setText(QApplication::translate("MainWindow", "Limits", Q_NULLPTR));
        pbReads->setText(QApplication::translate("MainWindow", "Reads", Q_NULLPTR));
        pb_alerts->setText(QApplication::translate("MainWindow", "Alerts", Q_NULLPTR));
        pbShutdown->setText(QApplication::translate("MainWindow", "Shutdown buzzer", Q_NULLPTR));
        lb_xbee->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
