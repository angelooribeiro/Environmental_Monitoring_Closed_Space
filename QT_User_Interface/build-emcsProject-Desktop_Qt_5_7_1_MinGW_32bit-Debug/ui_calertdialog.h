/********************************************************************************
** Form generated from reading UI file 'calertdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALERTDIALOG_H
#define UI_CALERTDIALOG_H

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

class Ui_CAlertDialog
{
public:
    QTableView *tableView;
    QLabel *label;
    QLabel *lb_error;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QDateEdit *dateEdit_Limit;
    QComboBox *comboBox_limit;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_submit;
    QPushButton *pb_Refresh;
    QPushButton *pb_close;

    void setupUi(QDialog *CAlertDialog)
    {
        if (CAlertDialog->objectName().isEmpty())
            CAlertDialog->setObjectName(QStringLiteral("CAlertDialog"));
        CAlertDialog->resize(776, 400);
        tableView = new QTableView(CAlertDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 50, 761, 251));
        label = new QLabel(CAlertDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 9, 98, 23));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        lb_error = new QLabel(CAlertDialog);
        lb_error->setObjectName(QStringLiteral("lb_error"));
        lb_error->setGeometry(QRect(10, 30, 101, 16));
        widget = new QWidget(CAlertDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(600, 310, 174, 85));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        dateEdit_Limit = new QDateEdit(widget);
        dateEdit_Limit->setObjectName(QStringLiteral("dateEdit_Limit"));

        verticalLayout_2->addWidget(dateEdit_Limit);

        comboBox_limit = new QComboBox(widget);
        comboBox_limit->setObjectName(QStringLiteral("comboBox_limit"));

        verticalLayout_2->addWidget(comboBox_limit);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pb_submit = new QPushButton(widget);
        pb_submit->setObjectName(QStringLiteral("pb_submit"));

        verticalLayout->addWidget(pb_submit);

        pb_Refresh = new QPushButton(widget);
        pb_Refresh->setObjectName(QStringLiteral("pb_Refresh"));

        verticalLayout->addWidget(pb_Refresh);

        pb_close = new QPushButton(widget);
        pb_close->setObjectName(QStringLiteral("pb_close"));

        verticalLayout->addWidget(pb_close);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(CAlertDialog);

        QMetaObject::connectSlotsByName(CAlertDialog);
    } // setupUi

    void retranslateUi(QDialog *CAlertDialog)
    {
        CAlertDialog->setWindowTitle(QApplication::translate("CAlertDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("CAlertDialog", "Alerts Table", Q_NULLPTR));
        lb_error->setText(QString());
        label_3->setText(QApplication::translate("CAlertDialog", "Select date:", Q_NULLPTR));
        comboBox_limit->clear();
        comboBox_limit->insertItems(0, QStringList()
         << QApplication::translate("CAlertDialog", "Select Limit", Q_NULLPTR)
         << QApplication::translate("CAlertDialog", "CO2", Q_NULLPTR)
         << QApplication::translate("CAlertDialog", "Temp. High", Q_NULLPTR)
         << QApplication::translate("CAlertDialog", "Temp. Low", Q_NULLPTR)
         << QApplication::translate("CAlertDialog", "Hum. High", Q_NULLPTR)
         << QApplication::translate("CAlertDialog", "Hum. Low", Q_NULLPTR)
        );
        pb_submit->setText(QApplication::translate("CAlertDialog", "Submit", Q_NULLPTR));
        pb_Refresh->setText(QApplication::translate("CAlertDialog", "Refresh", Q_NULLPTR));
        pb_close->setText(QApplication::translate("CAlertDialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CAlertDialog: public Ui_CAlertDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALERTDIALOG_H
