#ifndef CDATABASE_H
#define CDATABASE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>

#include "parameters.h"

class QSqlTableModel;
class QSqlQuery;

class CDataBase : public QWidget
{
    Q_OBJECT

public:
    explicit CDataBase(QWidget *parent = 0);
    static CDataBase& getInstance();
    bool db_connect(void);
    ~CDataBase();

private:
    static CDataBase* m_instance;
    QSqlDatabase m_database;
    QSqlQuery m_query;
    QSqlQueryModel queryModel;

};

#endif // CDATABASE_H
