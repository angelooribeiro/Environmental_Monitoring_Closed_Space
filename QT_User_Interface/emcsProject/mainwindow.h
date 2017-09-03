#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QPixmap>
#include <QSqlQuery>
#include <QDate>
#include <QTime>

#include "cdatabase.h"
#include "cprmdialog.h"
#include "parameters.h"
#include "readdialog.h"
#include "calertdialog.h"

namespace Ui {
class MainWindow;
}
class CDataBase;
class CPrmDialog;
class ReadDialog;
class CAlertDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    // method get that return's the socket descriptor
    quintptr get_socket_desc();

    ~MainWindow();

public slots:
    // handle when cliente connection is detected
    void newConnection();
    // handle when bytes are received in the socket
    void readyRead();
    // hnadle when cliente disconnect from tcp server
    void disconnected();

private slots:
    void on_pb_logo_clicked();
    void on_pb_ChangePrm_clicked();
    void on_pbReads_clicked();
    void on_pbShutdown_clicked();
    void on_pb_alerts_clicked();

private:
    Ui::MainWindow *ui;

    QTcpServer *m_server;
    QTcpSocket *m_socket;
    QSqlQuery m_query;

    CPrmDialog *m_prm;
    ReadDialog *m_read;
    CAlertDialog *m_alert;

    quintptr socket_desc;
    int buzzer;
};

#endif // MAINWINDOW_H
