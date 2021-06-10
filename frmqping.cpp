#include "frmqping.h"
#include "ui_frmqping.h"
#include <QHostAddress>
#include <QDebug>
#include "app.h"

frmQPing::frmQPing(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::frmQPing)
{
    ui->setupUi(this);
    this->UiInit();

    m_timer = new QTimer();
    QObject::connect(m_timer, &QTimer::timeout,
                     this, &frmQPing::TimerOut);
}

frmQPing::~frmQPing()
{
    delete ui;
}

void frmQPing::UiInit()
{
    QString strStartAddr = App::settings.value("Start_Addr", "192.168.1.1").toString();
    QString srrEndAddr   = App::settings.value("End_Addr", "192.168.1.200").toString();
    int timInter = App::settings.value("TimeInterval", "20").toInt();

    ui->lineEdit_startAddr->setText(strStartAddr);
    ui->lineEdit_endAddr->setText(srrEndAddr);
    ui->spinBox->setValue(timInter);

    /*设置表格是否充满，即行末不留空*/
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    /*设置tablewidget等宽*/
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->horizontalHeader()->hide();                      // 隐藏列头
    ui->tableWidget->verticalHeader()->hide();                          // 隐藏行头
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(22);       // 设置行高
    //设置列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidget->horizontalHeader()->resizeSection(0, 100);
    ui->tableWidget->horizontalHeader()->resizeSection(1, 40);
    // 设置表格内容不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 表格使用交替色填充
    ui->tableWidget->setAlternatingRowColors(true);
    // 行选中模式
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void frmQPing::TimerOut()
{
    //qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    m_ping.at(m_timerCount % m_countAddr)->executePingComman();
    m_timerCount++;

    //if(m_ip > m_endAddr) {
    //    m_timer->stop();
    //    ui->pushButton->setEnabled(true);
    //}

}

void frmQPing::PingResult(quint32 ip, quint32 id, int s, quint32 timeOutConut, quint32 pingCount)      // Ping结果
{
    if(s == 0) {
        m_pLightButton.at(id)->setRed();
    }
    else {
        m_pLightButton.at(id)->setGreen();
    }

    QString str = QHostAddress(ip).toString()
            + ((s == 1)?" Ping Ok":" Ping Timer Out")
            + QString("  [%1 / %2]").arg(timeOutConut).arg(pingCount);

    ui->tableWidget->setItem(id, 2, new QTableWidgetItem(str));
    ui->tableWidget->item(id, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}

// 开始停止按键
void frmQPing::on_pushButton_clicked()
{
    if(m_bIsRun) {
        ui->pushButton->setText("开始");
        ui->lineEdit_startAddr->setEnabled(true);
        ui->lineEdit_endAddr->setEnabled(true);
        ui->spinBox->setEnabled(true);
        m_bIsRun = false;
        stop();
    }
    else {
        App::settings.setValue("Start_Addr", ui->lineEdit_startAddr->text());
        App::settings.setValue("End_Addr", ui->lineEdit_endAddr->text());
        App::settings.setValue("TimeInterval", ui->spinBox->value());

        ui->pushButton->setText("停止");
        ui->lineEdit_startAddr->setEnabled(false);
        ui->lineEdit_endAddr->setEnabled(false);
        ui->spinBox->setEnabled(false);
        m_bIsRun = true;
        start();
    }
}

void frmQPing::stop()
{
    m_timer->stop();
}
void frmQPing::start()
{
    // 时间间隔
    m_tim = ui->spinBox->value();
    // 开始地址
    m_startAddr = QHostAddress(ui->lineEdit_startAddr->text()).toIPv4Address();
    // 终止地址
    m_endAddr = QHostAddress(ui->lineEdit_endAddr->text()).toIPv4Address();
    // 统计一共多少个IP
    m_countAddr = m_endAddr - m_startAddr;

    ui->tableWidget->clearContents();   //清空表格中的内容（不包含表头）。
    ui->tableWidget->setRowCount(m_countAddr);

    m_pLightButton.clear();
    m_ping.clear();

    for(quint32 ip = m_startAddr; ip < m_endAddr; ip++) {
        quint32 id = ip - m_startAddr;
        ui->tableWidget->setItem(id, 0, new QTableWidgetItem(QHostAddress(ip).toString()));
        ui->tableWidget->item(id, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        LightButton *pLB = new LightButton();
        m_pLightButton.append(pLB);
        ui->tableWidget->setCellWidget(id, 1, pLB);
        QPing *p = new QPing(ip, id);
        QObject::connect(p, &QPing::signal_pingOk,
                     this, &frmQPing::PingResult);
        m_ping.append(p);
    }

    m_timer->start(m_tim);
}
