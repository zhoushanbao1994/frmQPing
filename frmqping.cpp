#include "frmqping.h"
#include "ui_frmqping.h"
#include <QHostAddress>

frmQPing::frmQPing(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::frmQPing)
{
    ui->setupUi(this);

    m_ping = new QPing(QHostAddress("127.0.0.1").toIPv4Address());
    QObject::connect(m_ping, &QPing::signal_pingOk,
                     [&] (quint32 ip, int s){
       QString str = QHostAddress(ip).toString() + ((s == 1)?" Ping Ok":" Ping Timer Out");
       ui->textEdit->append(str);
    });

    m_timer = new QTimer();
    QObject::connect(m_timer, &QTimer::timeout,
                     [&] {
        m_ping->setPingParameter(m_ip);
        m_ping->executePingComman();
        m_ip++;
        if(m_ip > m_endAddr) {
            m_timer->stop();
            ui->pushButton->setEnabled(true);
        }
    });
}

frmQPing::~frmQPing()
{
    delete ui;
}


void frmQPing::on_pushButton_clicked()
{
    m_tim = ui->spinBox->value();
    m_startAddr = QHostAddress(ui->lineEdit_startAddr->text()).toIPv4Address();
    m_endAddr = QHostAddress(ui->lineEdit_endAddr->text()).toIPv4Address();

    m_ip = m_startAddr;

    m_timer->start(m_tim);
    ui->pushButton->setEnabled(false);
}
