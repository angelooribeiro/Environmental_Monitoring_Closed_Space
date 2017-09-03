 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parameters.h"

Parameters_last prm_last;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set logo as background image of button
    ui->pb_logo->setStyleSheet("background-image:url(/Users/gnhob/Documents/QT_Final_EMCS/emcsProject/logo_v2.png);");
    // set lables and buttons
    ui->lb_status->setStyleSheet("QLabel {color : red; }");
    ui->lb_client->hide();
    ui->lb_xbee->hide();
    ui->pbShutdown->hide();

    // Fill parameters with the last limits in db
    m_query.exec("SELECT * FROM tab_parameter");
    m_query.last();
    prm_last.co2 = m_query.value(1).toFloat();
    prm_last.temp_max = m_query.value(2).toFloat();
    prm_last.temp_min = m_query.value(3).toFloat();
    prm_last.hum_max = m_query.value(4).toFloat();
    prm_last.hum_min = m_query.value(5).toFloat();
    prm_last.sim = m_query.value(6).toFloat();

}

quintptr MainWindow::get_socket_desc()
{
    return socket_desc;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_logo_clicked()
{
    m_server = new QTcpServer(this);
    int port = 1234;

    if(!m_server->listen(QHostAddress::AnyIPv4, port))
    {
        qDebug() << "ERROR: Could not start server";
          QMessageBox::information(this,"Sucess","Server started, listen port 1234");
    }
    else
    {
        // every time client connects to the server, newConnection signal is emitted
        // and the newConnection is the slot that handle the new connection

        connect(m_server,SIGNAL(newConnection()),this,SLOT(newConnection()));
        qDebug() << "Server started: listening to port "<<port<< "...";

        ui->lb_status->setText("Server started");
        ui->lb_status->setStyleSheet("QLabel {color : green; }");
        ui->lb_client->show();
    }
}

void MainWindow::newConnection()
{
    qDebug() << "Client connected";
    //QMessageBox::information(this,"Server","Client connected");
    ui->lb_client->setText("Client connected");
    ui->lb_status->setStyleSheet("QLabel {color : green; }");

    m_socket = m_server->nextPendingConnection();
    socket_desc = m_socket->socketDescriptor();
    connect(m_socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(m_socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
}

void MainWindow::readyRead()
{

    QByteArray frameReceived;
    QString s_co2, s_temp, s_hum;
    int i_aux = 0, x;
    float co2, temp, hum;

    // fill Data array while data are avaliable in socket
    while(m_socket->bytesAvailable())
        frameReceived.append(m_socket->readAll());

    qDebug() <<"Data received: " <<frameReceived;

    char c_aux1 = frameReceived.at(0);
    char c_aux2 = frameReceived.at(1);
    //char c_aux2 = 'O';

    // Buzzer ON
    if(c_aux1 == 'B' && c_aux2 == 'O')
    {
        qDebug() << "CO2 out of limits";
        //QMessageBox::information(this,"ALERT","CO2 out of limits, interface blocked");
        ui->lb_xbee->setText("CO2 Alert!");
        ui->lb_xbee->setStyleSheet("QLabel {color : red; }");

        buzzer = 1;
        //unblock Shutdown button
        ui->pbShutdown->show();
        // block push buttons
        ui->pb_ChangePrm->setEnabled(false);
        ui->pbReads->setEnabled(false);
        ui->pb_alerts->setEnabled(false);
    }
    // new parameters frame
    if (c_aux1 == 'N' && c_aux2 == 'V')
    {
        for (int i = 2 ; i < frameReceived.size() ; i++)
        {
            char aux = frameReceived.at(i);

            if((i_aux == 0) && (aux != '+'))
            {
                x = i-2;
                s_temp.insert(x,aux);
            }
            if((i_aux == 1)&& (aux != '+'))
            {
                x = i-3;
                s_hum.insert(x,aux);
            }
            if((i_aux == 2) && (aux != '+'))
            {
                x = i-4;
                s_co2.insert(x,aux);
            }
            if(aux == '+')
                i_aux++;
        }

        // convert strings to floats
        co2 = s_co2.toFloat();
        temp = s_temp.toFloat();
        hum = s_hum.toFloat();

        // get the last id limit
        m_query.exec("SELECT * FROM tab_parameter");
        m_query.last();
        int last_id_parameter = m_query.value(0).toFloat();

        QDate date = QDate::currentDate();
        QTime time = QTime::currentTime();

        // fill new data in BD
        m_query.prepare("INSERT INTO tab_read (id_Parameter, hum, tem, co2, date_read, time_read) "
                        "VALUES (:id,:co2,:temp,:hum,:date,:time)");

        m_query.bindValue(":id",last_id_parameter);
        m_query.bindValue(":co2",co2);
        m_query.bindValue(":temp",temp);
        m_query.bindValue(":hum",hum);
        m_query.bindValue(":date",date);
        m_query.bindValue(":time",time);
        m_query.exec();

        //Verify if parameters are out of limit
        /*
        if(co2 >= prm_last.co2)
        {
            qDebug() << "CO2 out of limits";
            //QMessageBox::information(this,"ALERT","CO2 out of limits, interface blocked");
            buzzer = 1;
            //unblock Shutdown button
            ui->pbShutdown->show();
            // block push buttons
            ui->pb_ChangePrm->setEnabled(false);
            ui->pbReads->setEnabled(false);
            ui->pb_alerts->setEnabled(false);
        }
        */
        if(co2 > prm_last.co2)
        {
            ui->lb_xbee->setText("CO2 alert!");
            ui->lb_xbee->setStyleSheet("QLabel {color : red; }");
            qDebug() << "CO2 out of limtis";
            //QMessageBox::information(this,"ALERT","Temperature out of limits");
        }
        if(temp > prm_last.temp_max || temp < prm_last.temp_min)
        {
            ui->lb_xbee->setText("Temperature alert!");
            ui->lb_xbee->setStyleSheet("QLabel {color : red; }");
            qDebug() << "Temperature out of limtis";
            //QMessageBox::information(this,"ALERT","Temperature out of limits");
        }
        if(hum > prm_last.hum_max || hum < prm_last.hum_min)
        {
            ui->lb_xbee->setText("Humidity alert!");
            ui->lb_xbee->setStyleSheet("QLabel {color : red; }");
            qDebug() << "Humidity out of limtis";
            //QMessageBox::information(this,"ALERT","Humidity out of limits");
        }

    }


    // Buzzer OFF
    if(c_aux1 == 'B' && c_aux2 == 'F')
    {
        buzzer = 0;
        // unblock push buttons
        ui->pb_ChangePrm->setEnabled(true);
        ui->pbReads->setEnabled(true);
        ui->pb_alerts->setEnabled(true);
        ui->pbShutdown->hide();
    }

    // Xbee not connected
    if(c_aux1 == 'X' && c_aux2 == 'D')
    {
        ui->lb_xbee->setText("Xbee not connected");
        ui->lb_xbee->setStyleSheet("QLabel {color : red; }");
    }

    // Error feedback on limits
    if(c_aux1 == 'E' && c_aux2 == 'F')
    {
        QMessageBox::information(this,"Error","Parameter not updated");
    }

    // Xbee low battery
    if(c_aux1 == 'L' && c_aux2 == 'B')
    {
        QMessageBox::information(this,"ALERT","Low battery on XBee (15%)");
    }
}

void MainWindow::disconnected()
{
    qDebug() << "Client disconnected";
    ui->lb_client->setText("Client disconnected");
    ui->lb_client->setStyleSheet("QLabel {color : red; }");

    m_socket->deleteLater();

}

void MainWindow::on_pb_ChangePrm_clicked()
{
    socket_desc = get_socket_desc();
    m_prm = new CPrmDialog(this, socket_desc);
    m_prm->show();
    qDebug() << "Change Parameters window has been opened";
}

void MainWindow::on_pbReads_clicked()
{   
    m_read = new ReadDialog(this);
    m_read->show();
    qDebug() << "Reads window has been opened";
}

void MainWindow::on_pbShutdown_clicked()
{
    m_socket->write("BO");
    qDebug() << "aqui";
}

void MainWindow::on_pb_alerts_clicked()
{
    m_alert = new CAlertDialog(this);
    m_alert->show();
    qDebug() << "Alert window has been opened";
}
