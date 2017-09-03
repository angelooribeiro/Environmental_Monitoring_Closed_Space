#include "calertdialog.h"
#include "ui_calertdialog.h"

CAlertDialog::CAlertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAlertDialog)
{
    ui->setupUi(this);

    q_model = new QSqlQueryModel();
    setTable();
    date = QDate::currentDate();
}

CAlertDialog::~CAlertDialog()
{
    delete ui;
}

void CAlertDialog::on_pb_close_clicked()
{
    this->close();
}

void CAlertDialog::on_pb_submit_clicked()
{
    //QString prm_str = ui->lineEdit_prm->text();
    int i_prm = ui->comboBox_limit->currentIndex();
    QDate selected_date = ui->dateEdit_Limit->date();
    QDate default_date = QDate(2000,1,1);

    // if User selected limit
    if(i_prm != 0 && selected_date == default_date)
    {
        ui->lb_error->hide();
        switch (i_prm) {
            case 1:
                m_query.exec("SELECT tab_read.CO2, tab_parameter.CO2_Limit, tab_read.date_read, tab_read.time_read FROM tab_read,tab_parameter "
                                 "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                                 "AND tab_read.co2>tab_parameter.CO2_Limit");

                q_model->setHeaderData(0, Qt::Horizontal, tr("CO2"));
                q_model->setHeaderData(1, Qt::Horizontal, tr("CO2 Limit"));

                break;
            case 2:
                m_query.exec("SELECT tab_read.tem, tab_parameter.Upper_Temperature, tab_read.date_read, tab_read.time_read FROM tab_read,tab_parameter "
                                 "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                                 "AND tab_read.tem>tab_parameter.Upper_Temperature");

                q_model->setHeaderData(0, Qt::Horizontal, tr("Temperature"));
                q_model->setHeaderData(1, Qt::Horizontal, tr("Tem. Max."));

                break;

            case 3:
                m_query.exec("SELECT tab_read.tem, tab_parameter.Lower_Temperature, tab_read.date_read, tab_read.time_read FROM tab_read,tab_parameter "
                                 "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                                 "AND tab_read.tem<tab_parameter.Lower_Temperature");

                q_model->setHeaderData(0, Qt::Horizontal, tr("Temperature"));
                q_model->setHeaderData(1, Qt::Horizontal, tr("Tem. Min."));

                break;

            case 4:
                m_query.exec("SELECT tab_read.hum, tab_parameter.Upper_Humidity, tab_read.date_read, tab_read.time_read FROM tab_read,tab_parameter "
                                 "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                                 "AND tab_read.hum>tab_parameter.Upper_Humidity");

                q_model->setHeaderData(0, Qt::Horizontal, tr("Humidity"));
                q_model->setHeaderData(1, Qt::Horizontal, tr("Hum. Max."));

                break;

            case 5:
                m_query.exec("SELECT tab_read.hum, tab_parameter.Lower_Humidity, tab_read.date_read, tab_read.time_read FROM tab_read,tab_parameter "
                                 "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                                 "AND tab_read.hum<tab_parameter.Lower_Humidity)");

                q_model->setHeaderData(0, Qt::Horizontal, tr("Humidity"));
                q_model->setHeaderData(1, Qt::Horizontal, tr("Hum. Min."));

                break;

            default:
                break;
        }

        q_model->setQuery(m_query);
        q_model->setHeaderData(2, Qt::Horizontal, tr("read date"));
        q_model->setHeaderData(3, Qt::Horizontal, tr("read time"));
        ui->tableView->setModel(q_model);
        for (int i=0;i<=4 ;i++)
            ui->tableView->setColumnWidth(i,75);
    }

    // If user select date
    if(i_prm == 0 && selected_date != default_date)
    {
        ui->lb_error->hide();
        m_query.prepare("SELECT tab_read.CO2, tab_parameter.CO2_Limit,tab_read.tem, tab_parameter.Upper_Temperature, "
                                    "tab_parameter.Lower_Temperature, tab_read.hum,tab_parameter.Upper_Humidity, "
                                    "tab_parameter.Lower_Humidity,tab_read.date_read, tab_read.time_read "
                        "FROM tab_read,tab_parameter "
                         "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                         "AND tab_read.date_read=:selected_date "
                         "AND (tab_read.co2>tab_parameter.CO2_Limit "
                                    "OR tab_read.tem>tab_parameter.Upper_Temperature "
                                    "OR tab_read.tem<tab_parameter.Lower_Temperature "
                                    "OR tab_read.hum>tab_parameter.Upper_Humidity "
                                    "OR tab_read.hum<tab_parameter.Lower_Humidity)");
        m_query.bindValue(":selected_date",selected_date);
        m_query.exec();

        q_model->setQuery(m_query);
        ui->tableView->setModel(q_model);
        for (int i=0;i<=10 ;i++)
            ui->tableView->setColumnWidth(i,75);
    }

    // If user select date and limit
    if(i_prm != 0 && selected_date != default_date)
    {
        ui->lb_error->hide();
        switch (i_prm) {
        case 1:
            m_query.prepare("SELECT tab_read.CO2, tab_parameter.CO2_Limit, tab_read.date_read, tab_read.time_read "
                            "FROM tab_read,tab_parameter "
                            "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                            "AND tab_read.date_read=:selected_date "
                            "AND tab_read.co2>tab_parameter.CO2_Limit");
            m_query.bindValue(":selected_date",selected_date);
            m_query.exec();

            q_model->setHeaderData(0, Qt::Horizontal, tr("CO2"));
            q_model->setHeaderData(1, Qt::Horizontal, tr("CO2 Limit"));

            break;

        case 2:
            m_query.prepare("SELECT tab_read.tem, tab_parameter.Upper_Temperature, tab_read.date_read, tab_read.time_read "
                            "FROM tab_read,tab_parameter "
                            "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                            "AND tab_read.date_read=:selected_date "
                            "AND tab_read.tem>tab_parameter.Upper_Temperature");
            m_query.bindValue(":selected_date",selected_date);
            m_query.exec();

            q_model->setHeaderData(0, Qt::Horizontal, tr("Temperature"));
            q_model->setHeaderData(1, Qt::Horizontal, tr("Tem. Max."));

            break;

        case 3:
            m_query.prepare("SELECT tab_read.tem, tab_parameter.Lower_Temperature, tab_read.date_read, tab_read.time_read "
                            "FROM tab_read,tab_parameter "
                            "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                            "AND tab_read.date_read=:selected_date "
                            "AND tab_read.tem<tab_parameter.Lower_Temperature");
            m_query.bindValue(":selected_date",selected_date);
            m_query.exec();

            q_model->setHeaderData(0, Qt::Horizontal, tr("Temperature"));
            q_model->setHeaderData(1, Qt::Horizontal, tr("Tem. Min."));

            break;

        case 4:
            m_query.prepare("SELECT tab_read.hum, tab_parameter.Upper_Humidity, tab_read.date_read, tab_read.time_read "
                            "FROM tab_read,tab_parameter "
                            "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                            "AND tab_read.date_read=:selected_date "
                            "AND tab_read.hum>tab_parameter.Upper_Humidity");
            m_query.bindValue(":selected_date",selected_date);
            m_query.exec();

            q_model->setHeaderData(0, Qt::Horizontal, tr("Humidity"));
            q_model->setHeaderData(1, Qt::Horizontal, tr("Hum. Max."));

            break;

        case 5:
            m_query.prepare("SELECT tab_read.hum, tab_parameter.Lower_Humidity, tab_read.date_read, tab_read.time_read "
                            "FROM tab_read,tab_parameter "
                            "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                            "AND tab_read.date_read=:selected_date "
                            "AND tab_read.hum<tab_parameter.Lower_Humidity");
            m_query.bindValue(":selected_date",selected_date);
            m_query.exec();

            q_model->setHeaderData(0, Qt::Horizontal, tr("Humidity"));
            q_model->setHeaderData(1, Qt::Horizontal, tr("Hum. Min."));

            break;

        default:
            break;
        }

        q_model->setQuery(m_query);
        q_model->setHeaderData(2, Qt::Horizontal, tr("read date"));
        q_model->setHeaderData(3, Qt::Horizontal, tr("read time"));

        ui->tableView->setModel(q_model);
        for (int i=0;i<=4 ;i++)
            ui->tableView->setColumnWidth(i,75);
    }

    if(i_prm == 0 && selected_date == default_date)
    {
        ui->lb_error->setText("Select parameter");
        ui->lb_error->setStyleSheet("QLabel {color : red; }");
        ui->lb_error->show();
    }
}

void CAlertDialog::on_pb_Refresh_clicked()
{
    setTable();
}

void CAlertDialog::setTable(void)
{
    m_query.exec("SELECT tab_read.co2,tab_parameter.CO2_Limit,"
                 "tab_read.tem,tab_parameter.Upper_Temperature,tab_parameter.Lower_Temperature,"
                 "tab_read.hum,tab_parameter.Upper_Humidity,tab_parameter.Lower_Humidity,"
                 "tab_read.date_read, tab_read.time_read "
                 "FROM tab_read,tab_parameter "
                 "WHERE tab_read.id_Parameter=tab_parameter.id_Parameter "
                    "AND (tab_read.co2>tab_parameter.CO2_Limit "
                    "OR tab_read.tem>tab_parameter.Upper_Temperature "
                    "OR tab_read.tem<tab_parameter.Lower_Temperature "
                    "OR tab_read.hum>tab_parameter.Upper_Humidity "
                    "OR tab_read.hum<tab_parameter.Lower_Humidity)");

    q_model->setQuery(m_query);

    q_model->setHeaderData(0, Qt::Horizontal, tr("CO2"));
    q_model->setHeaderData(1, Qt::Horizontal, tr("CO2 limit"));
    q_model->setHeaderData(2, Qt::Horizontal, tr("Temperature"));
    q_model->setHeaderData(3, Qt::Horizontal, tr("Temp. Max."));
    q_model->setHeaderData(4, Qt::Horizontal, tr("Temp. Min."));
    q_model->setHeaderData(5, Qt::Horizontal, tr("Humidity"));
    q_model->setHeaderData(6, Qt::Horizontal, tr("Hum. Max."));
    q_model->setHeaderData(7, Qt::Horizontal, tr("Hum. Min."));
    q_model->setHeaderData(8, Qt::Horizontal, tr("read date"));
    q_model->setHeaderData(9, Qt::Horizontal, tr("read time"));

    ui->tableView->setModel(q_model);

    for (int i=0;i<=9 ;i++)
        ui->tableView->setColumnWidth(i,75);

}
