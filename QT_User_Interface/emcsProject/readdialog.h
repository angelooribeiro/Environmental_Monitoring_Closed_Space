#ifndef READDIALOG_H
#define READDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QTime>
#include <QDate>
#include <QDebug>

#include "cdatabase.h"

namespace Ui {
class ReadDialog;
}

class CDataBase;

class ReadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReadDialog(QWidget *parent = 0);
    ~ReadDialog();

private slots:
    void on_pbClose_clicked();
    void on_pb_Submit_clicked();

    void on_pb_Refresh_clicked();

private:
    Ui::ReadDialog *ui;
   //QSqlQueryModel query;
    QSqlTableModel *m_tabmodel;
    QSqlQueryModel *q_model;
    QSqlQuery m_query;
    QDate date;
};

#endif // READDIALOG_H
