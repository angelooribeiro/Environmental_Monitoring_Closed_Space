#include "mainwindow.h"
#include "cprmdialog.h"
#include "cdatabase.h"
#include "parameters.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CDataBase::getInstance().db_connect();
    MainWindow w;
    w.show();

    return a.exec();
}
