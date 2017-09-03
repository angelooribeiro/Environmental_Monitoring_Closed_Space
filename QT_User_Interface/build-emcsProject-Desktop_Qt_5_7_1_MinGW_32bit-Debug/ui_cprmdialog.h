/********************************************************************************
** Form generated from reading UI file 'cprmdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPRMDIALOG_H
#define UI_CPRMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPrmDialog
{
public:
    QLabel *label_2;
    QLabel *lb_server;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView_Limits;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_sim;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_prm;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_prm;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_Submit;
    QPushButton *pb_Refresh;
    QPushButton *pb_close;

    void setupUi(QDialog *CPrmDialog)
    {
        if (CPrmDialog->objectName().isEmpty())
            CPrmDialog->setObjectName(QStringLiteral("CPrmDialog"));
        CPrmDialog->resize(597, 323);
        label_2 = new QLabel(CPrmDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(11, 11, 99, 23));
        QFont font;
        font.setPointSize(14);
        label_2->setFont(font);
        lb_server = new QLabel(CPrmDialog);
        lb_server->setObjectName(QStringLiteral("lb_server"));
        lb_server->setGeometry(QRect(10, 40, 161, 16));
        widget = new QWidget(CPrmDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 60, 581, 256));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tableView_Limits = new QTableView(widget);
        tableView_Limits->setObjectName(QStringLiteral("tableView_Limits"));
        QFont font1;
        font1.setPointSize(9);
        tableView_Limits->setFont(font1);

        verticalLayout_2->addWidget(tableView_Limits);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(17, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        lineEdit_sim = new QLineEdit(widget);
        lineEdit_sim->setObjectName(QStringLiteral("lineEdit_sim"));

        horizontalLayout_2->addWidget(lineEdit_sim);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox_prm = new QComboBox(widget);
        comboBox_prm->setObjectName(QStringLiteral("comboBox_prm"));

        horizontalLayout->addWidget(comboBox_prm);

        horizontalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lineEdit_prm = new QLineEdit(widget);
        lineEdit_prm->setObjectName(QStringLiteral("lineEdit_prm"));

        horizontalLayout->addWidget(lineEdit_prm);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pb_Submit = new QPushButton(widget);
        pb_Submit->setObjectName(QStringLiteral("pb_Submit"));

        verticalLayout->addWidget(pb_Submit);

        pb_Refresh = new QPushButton(widget);
        pb_Refresh->setObjectName(QStringLiteral("pb_Refresh"));

        verticalLayout->addWidget(pb_Refresh);

        pb_close = new QPushButton(widget);
        pb_close->setObjectName(QStringLiteral("pb_close"));

        verticalLayout->addWidget(pb_close);


        gridLayout_2->addLayout(verticalLayout, 0, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        retranslateUi(CPrmDialog);

        QMetaObject::connectSlotsByName(CPrmDialog);
    } // setupUi

    void retranslateUi(QDialog *CPrmDialog)
    {
        CPrmDialog->setWindowTitle(QApplication::translate("CPrmDialog", "Dialog", Q_NULLPTR));
        label_2->setText(QApplication::translate("CPrmDialog", "Limits Table", Q_NULLPTR));
        lb_server->setText(QString());
        label->setText(QApplication::translate("CPrmDialog", "Insert New SIM n\302\272:", Q_NULLPTR));
        comboBox_prm->clear();
        comboBox_prm->insertItems(0, QStringList()
         << QApplication::translate("CPrmDialog", "New Limit", Q_NULLPTR)
         << QApplication::translate("CPrmDialog", "Max. Co2", Q_NULLPTR)
         << QApplication::translate("CPrmDialog", "Max. Temp.", Q_NULLPTR)
         << QApplication::translate("CPrmDialog", "Min. Temp.", Q_NULLPTR)
         << QApplication::translate("CPrmDialog", "Max. Hum.", Q_NULLPTR)
         << QApplication::translate("CPrmDialog", "Min. Hum.", Q_NULLPTR)
        );
        pb_Submit->setText(QApplication::translate("CPrmDialog", "Submit", Q_NULLPTR));
        pb_Refresh->setText(QApplication::translate("CPrmDialog", "Refresh", Q_NULLPTR));
        pb_close->setText(QApplication::translate("CPrmDialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CPrmDialog: public Ui_CPrmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPRMDIALOG_H
