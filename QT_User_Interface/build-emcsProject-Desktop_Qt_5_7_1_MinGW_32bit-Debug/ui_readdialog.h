/********************************************************************************
** Form generated from reading UI file 'readdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READDIALOG_H
#define UI_READDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReadDialog
{
public:
    QLabel *label;
    QLabel *lb_server;
    QTableView *tableView;
    QLabel *lb_error;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QDateEdit *dateEdit;
    QComboBox *comboBox_limit;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_Submit;
    QPushButton *pb_Refresh;
    QPushButton *pbClose;

    void setupUi(QDialog *ReadDialog)
    {
        if (ReadDialog->objectName().isEmpty())
            ReadDialog->setObjectName(QStringLiteral("ReadDialog"));
        ReadDialog->resize(409, 407);
        label = new QLabel(ReadDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 9, 103, 23));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        lb_server = new QLabel(ReadDialog);
        lb_server->setObjectName(QStringLiteral("lb_server"));
        lb_server->setGeometry(QRect(10, 40, 47, 16));
        tableView = new QTableView(ReadDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 60, 391, 241));
        lb_error = new QLabel(ReadDialog);
        lb_error->setObjectName(QStringLiteral("lb_error"));
        lb_error->setGeometry(QRect(10, 40, 101, 16));
        widget = new QWidget(ReadDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(200, 310, 195, 85));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));

        verticalLayout_2->addWidget(dateEdit);

        comboBox_limit = new QComboBox(widget);
        comboBox_limit->setObjectName(QStringLiteral("comboBox_limit"));

        verticalLayout_2->addWidget(comboBox_limit);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pb_Submit = new QPushButton(widget);
        pb_Submit->setObjectName(QStringLiteral("pb_Submit"));

        verticalLayout->addWidget(pb_Submit);

        pb_Refresh = new QPushButton(widget);
        pb_Refresh->setObjectName(QStringLiteral("pb_Refresh"));

        verticalLayout->addWidget(pb_Refresh);

        pbClose = new QPushButton(widget);
        pbClose->setObjectName(QStringLiteral("pbClose"));

        verticalLayout->addWidget(pbClose);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ReadDialog);

        QMetaObject::connectSlotsByName(ReadDialog);
    } // setupUi

    void retranslateUi(QDialog *ReadDialog)
    {
        ReadDialog->setWindowTitle(QApplication::translate("ReadDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("ReadDialog", "Reads Table", Q_NULLPTR));
        lb_server->setText(QString());
        lb_error->setText(QString());
        label_3->setText(QApplication::translate("ReadDialog", "(ex.: 2017/02/28)", Q_NULLPTR));
        comboBox_limit->clear();
        comboBox_limit->insertItems(0, QStringList()
         << QApplication::translate("ReadDialog", "Select Parameter", Q_NULLPTR)
         << QApplication::translate("ReadDialog", "CO2", Q_NULLPTR)
         << QApplication::translate("ReadDialog", "Temperature", Q_NULLPTR)
         << QApplication::translate("ReadDialog", "Humidity", Q_NULLPTR)
        );
        pb_Submit->setText(QApplication::translate("ReadDialog", "Submit", Q_NULLPTR));
        pb_Refresh->setText(QApplication::translate("ReadDialog", "Refresh", Q_NULLPTR));
        pbClose->setText(QApplication::translate("ReadDialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReadDialog: public Ui_ReadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READDIALOG_H
