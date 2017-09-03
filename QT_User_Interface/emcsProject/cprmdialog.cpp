#include "cprmdialog.h"
#include "ui_cprmdialog.h"
#include "parameters.h"

CPrmDialog::CPrmDialog(QWidget *parent, quintptr socket_des) :
    QDialog(parent),
    ui(new Ui::CPrmDialog),
    socket_d(socket_des)
{
    ui->setupUi(this);

    // create tabModel and fill it with tab_parameters (limits)
    m_tabmodel = new QSqlTableModel();
    setTable();

    QString sSim = QString::number(prm_last.sim);
    ui->lineEdit_sim->setText(sSim);

    // if not connected block submit button
    if (socket_des>2000)
    {
        ui->lb_server->setText("Client not connected");
        ui->lb_server->setStyleSheet("QLabel {color : red; }");
        ui->pb_Submit->setEnabled(false);
    }
    else
    {
        ui->lb_server->setEnabled(true);
        ui->pb_Submit->setEnabled(true);

        // create new tcp socket with the descriptor
        // of the original socket in mainwindow
        m_socket = new QTcpSocket();
        m_socket->setSocketDescriptor(socket_d);
    }
}

CPrmDialog::~CPrmDialog()
{
    delete ui;
}

void CPrmDialog::on_pb_Submit_clicked()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QByteArray frameSend;
    QString frameAux;
/*
    // get time
    QDate date_prm = QDate::currentDate();
    qDebug << "Date:" << date_prm;
*/
    // get values from UI
    QString sim_str = ui->lineEdit_sim->text();
    QString prm_str = ui->lineEdit_prm->text();
    int i_prm = ui->comboBox_prm->currentIndex(); // index parameter of combobox

    float f_prm = prm_str.toFloat();              // parameter on textEdit
    int i_sim = sim_str.toInt();                  // SIM nº on textEdit

    // new SIM number
    if(i_sim != 0 && i_prm == 0)
    {

        prm_last.sim = i_sim;
        frameAux = "NN" + QString::number(i_sim);
        frameSend = frameAux.toUtf8();
        m_socket->write(frameSend);

        m_query.prepare("INSERT INTO tab_parameter (CO2_Limit,Upper_Temperature,Lower_Temperature,Upper_Humidity,Lower_Humidity,Phone_number,date_parameter,time_parameter) "
                        "VALUES (:co2,:t_max,:t_min,:h_max,:h_min,:sim,:date,:time)");

        m_query.bindValue(":co2",prm_last.co2);
        m_query.bindValue(":t_max",prm_last.temp_max);
        m_query.bindValue(":t_min",prm_last.temp_min);
        m_query.bindValue(":h_max",prm_last.hum_max);
        m_query.bindValue(":h_min",prm_last.hum_min);
        m_query.bindValue(":sim",prm_last.sim);
        m_query.bindValue(":date",date);
        m_query.bindValue(":time",time);
        m_query.exec();

        qDebug() << frameSend;
    }
    // new limit
    if(i_prm != 0 && f_prm !=0)
    {
        ui->lb_server->show();
        switch (i_prm) {
        // new co2
        case 1:
                prm_last.co2 = f_prm;
                frameAux = "NC" + QString::number(f_prm);
                frameSend = frameAux.toUtf8();
                m_socket->write(frameSend);
            break;
        // new temperature HIGH
        case 2:
                prm_last.temp_max = f_prm;
                frameAux = "NTH" + QString::number(f_prm);
                frameSend = frameAux.toUtf8();
                m_socket->write(frameSend);
                qDebug() << "TH :" << frameSend;
            break;
        // new temperature LOW
        case 3:
                prm_last.temp_min = f_prm;
                frameAux = "NTL" + QString::number(f_prm);
                frameSend = frameAux.toUtf8();
                m_socket->write(frameSend);
            break;
        // new humidity HIGH
        case 4:
                prm_last.hum_max = f_prm;
                frameAux = "NHH" + QString::number(f_prm);
                frameSend = frameAux.toUtf8();
                m_socket->write(frameSend);
                qDebug() << "HH :" << frameSend;
            break;
        // new humidity LOW
        case 5:
                prm_last.hum_min = f_prm;
                frameAux = "NHL" + QString::number(f_prm);
                frameSend = frameAux.toUtf8();
                m_socket->write(frameSend);
            break;
        default:
            break;
        }

        m_query.prepare("INSERT INTO tab_parameter (CO2_Limit,Upper_Temperature,Lower_Temperature, "
                        "Upper_Humidity,Lower_Humidity,Phone_number,date_parameter,time_parameter) "
                        "VALUES (:co2,:t_max,:t_min,:h_max,:h_min,:sim,:date,:time)");

        m_query.bindValue(":co2",prm_last.co2);
        m_query.bindValue(":t_max",prm_last.temp_max);
        m_query.bindValue(":t_min",prm_last.temp_min);
        m_query.bindValue(":h_max",prm_last.hum_max);
        m_query.bindValue(":h_min",prm_last.hum_min);
        m_query.bindValue(":sim",prm_last.sim);
        m_query.bindValue(":date",date);
        m_query.bindValue(":time",time);        
        m_query.exec();
        qDebug() << frameSend;
    }

    if(i_sim != prm_last.sim)
    {
        prm_last.sim=i_sim;
        m_query.prepare("INSERT INTO tab_parameter (CO2_Limit,Upper_Temperature,Lower_Temperature, "
                        "Upper_Humidity,Lower_Humidity,Phone_number,date_parameter,time_parameter) "
                        "VALUES (:co2,:t_max,:t_min,:h_max,:h_min,:sim,:date,:time)");

        m_query.bindValue(":co2",prm_last.co2);
        m_query.bindValue(":t_max",prm_last.temp_max);
        m_query.bindValue(":t_min",prm_last.temp_min);
        m_query.bindValue(":h_max",prm_last.hum_max);
        m_query.bindValue(":h_min",prm_last.hum_min);
        m_query.bindValue(":sim",prm_last.sim);
        m_query.bindValue(":date",date);
        m_query.bindValue(":time",time);
        m_query.exec();
    }

    if(i_prm == 0  && i_sim == 0)
    {
        ui->lb_server->setText("No parameters introduced");
        ui->lb_server->setStyleSheet("QLabel {color : red; }");
        ui->lb_server->show();
        return;
    }

    if((i_prm != 0 && f_prm == 0) || (i_prm == 0 && f_prm != 0))
    {
        ui->lb_server->setText("Missing parameters");
        ui->lb_server->setStyleSheet("QLabel {color : red; }");
        ui->lb_server->show();
        return;
    }

}

void CPrmDialog::on_pb_close_clicked()
{
     this->close();
}

void CPrmDialog::on_pb_Refresh_clicked()
{
    setTable();
}

void CPrmDialog::setTable(void)
{
    m_tabmodel->setTable("tab_parameter");
    m_tabmodel->setHeaderData(0, Qt::Horizontal, tr("id"));
    m_tabmodel->setHeaderData(1, Qt::Horizontal, tr("CO2 max."));
    m_tabmodel->setHeaderData(2, Qt::Horizontal, tr("Max. temp."));
    m_tabmodel->setHeaderData(3, Qt::Horizontal, tr("Min. temp."));
    m_tabmodel->setHeaderData(4, Qt::Horizontal, tr("Max. hum."));
    m_tabmodel->setHeaderData(5, Qt::Horizontal, tr("Min. hum."));
    m_tabmodel->setHeaderData(6, Qt::Horizontal, tr("SIM nº"));
    m_tabmodel->setHeaderData(7, Qt::Horizontal, tr("Date"));
    m_tabmodel->setHeaderData(8, Qt::Horizontal, tr("Time"));
    m_tabmodel->select();

    ui->tableView_Limits->setModel(m_tabmodel);

    for (int i=0;i<=8 ;i++)
        ui->tableView_Limits->setColumnWidth(i,70);

    ui->tableView_Limits->hideColumn(0);
    ui->tableView_Limits->setEditTriggers(QAbstractItemView::NoEditTriggers);

    return;
}
