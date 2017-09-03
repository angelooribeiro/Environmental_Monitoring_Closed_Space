#ifndef CALERTDIALOG_H
#define CALERTDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>

#include "cdatabase.h"

namespace Ui {
class CAlertDialog;
}

class CDataBase;

class CAlertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAlertDialog(QWidget *parent = 0);
    ~CAlertDialog();
    void setTable(void);

private slots:
    void on_pb_close_clicked();
    void on_pb_submit_clicked();
    void on_pb_Refresh_clicked();

private:
    Ui::CAlertDialog *ui;
    QSqlQuery m_query;
    QSqlQueryModel *q_model;
    QDate date;
    //QTableView *tableView;
};

#endif // CALERTDIALOG_H
