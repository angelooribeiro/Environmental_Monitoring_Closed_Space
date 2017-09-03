#ifndef CPRMDIALOG_H
#define CPRMDIALOG_H

#include <QTcpSocket>
#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QSqlRecord>
#include <QDate>
#include <QTime>

#include "cdatabase.h"

namespace Ui {
class CPrmDialog;
}
class CDataBase;
class QTcpSocket;

class CPrmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CPrmDialog(QWidget *parent , quintptr socket_des);
    ~CPrmDialog();
    void setTable(void);
private slots:
    void on_pb_Submit_clicked();
    void on_pb_close_clicked();

    void on_pb_Refresh_clicked();

private:
    Ui::CPrmDialog *ui;
    QSqlQuery m_query;
    quintptr socket_d;
    CDataBase *m_db;
    QTcpSocket *m_socket;
    QSqlTableModel *m_tabmodel;

};

#endif // CPRMDIALOG_H
