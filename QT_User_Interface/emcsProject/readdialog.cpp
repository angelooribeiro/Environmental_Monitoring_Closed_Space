#include "readdialog.h"
#include "ui_readdialog.h"
#include <QMessageBox>

ReadDialog::ReadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadDialog)
{
    ui->setupUi(this);
    q_model = new QSqlQueryModel();

    // Fill Table View with all reads
    m_query.exec("SELECT tab_read.CO2, tab_read.tem, tab_read.hum, tab_read.date_read, tab_read.time_read "
                 "FROM tab_read");
    q_model->setQuery(m_query);
    ui->tableView->setModel(q_model);
    for (int i=0;i<=5 ;i++)
        ui->tableView->setColumnWidth(i,70);

}

ReadDialog::~ReadDialog()
{
    delete ui;
}

void ReadDialog::on_pbClose_clicked()
{
    this->close();
}

void ReadDialog::on_pb_Submit_clicked()
{
    int i_prm = ui->comboBox_limit->currentIndex();

    QDate selected_date = ui->dateEdit->date();
    QDate default_date = QDate(2000,1,1);

    // If User selected limit
    if (i_prm != 0 && selected_date == default_date)
    {
        switch (i_prm) {
            case 1:
                m_query.exec("SELECT CO2,date_read, time_read "
                             "FROM tab_read");
                break;

            case 2:
                m_query.exec("SELECT tem,date_read, time_read "
                             "FROM tab_read");
                break;

            case 3:
                m_query.exec("SELECT hum, date_read, time_read "
                             "FROM tab_read");
                break;

            default:
                break;
        }

        q_model->setQuery(m_query);
        ui->tableView->setModel(q_model);

        for (int i=0;i<=3 ;i++)
            ui->tableView->setColumnWidth(i,70);

    }

    //If User selects date
    if(i_prm == 0 && selected_date != default_date)
    {
        m_query.prepare("SELECT CO2,tem,hum,date_read,time_read "
                        "FROM tab_read "
                        "WHERE date_read=:selected_date");
        m_query.bindValue(":selected_date",selected_date);
        m_query.exec();

        q_model->setQuery(m_query);
        ui->tableView->setModel(q_model);

        for (int i=0;i<=5 ;i++)
            ui->tableView->setColumnWidth(i,70);
    }

    //If User selects both
    if(i_prm !=0 && selected_date != default_date)
    {
       switch (i_prm) {
           case 1:
               m_query.prepare("SELECT tab_read.CO2, tab_read.date_read, tab_read.time_read "
                               "FROM tab_read "
                               "WHERE tab_read.date_read=:date");
               m_query.bindValue(":date",selected_date);
               m_query.exec();
               break;

           case 2:
               m_query.prepare("SELECT tab_read.tem, tab_read.date_read, tab_read.time_read "
                               "FROM tab_read "
                               "WHERE tab_read.date_read=:date");
               m_query.bindValue(":date",selected_date);
               m_query.exec();
               break;

           case 3:
               m_query.prepare("SELECT tab_read.hum, tab_read.date_read, tab_read.time_read "
                               "FROM tab_read "
                               "WHERE tab_read.date_read=:date");
               m_query.bindValue(":date",selected_date);
               m_query.exec();
               break;

           default:
               break;
        }

        q_model->setQuery(m_query);
        ui->tableView->setModel(q_model);

        for (int i=0;i<=3 ;i++)
            ui->tableView->setColumnWidth(i,70);
    }

    // If User Selects nothing
    if(i_prm ==0 && selected_date == default_date)
    {
        m_query.exec("SELECT tab_read.CO2, tab_read.tem, tab_read.hum, tab_read.date_read, tab_read.time_read "
                     "FROM tab_read");
        q_model->setQuery(m_query);
        ui->tableView->setModel(q_model);
        for (int i=0;i<=5 ;i++)
            ui->tableView->setColumnWidth(i,70);

        QMessageBox::information(this,"Error","Choose parameter");
        return;
    }
}


void ReadDialog::on_pb_Refresh_clicked()
{
    m_query.exec("SELECT tab_read.CO2, tab_read.tem, tab_read.hum, tab_read.date_read, tab_read.time_read "
                 "FROM tab_read");
    q_model->setQuery(m_query);
    ui->tableView->setModel(q_model);
    for (int i=0;i<=5 ;i++)
        ui->tableView->setColumnWidth(i,70);
}
