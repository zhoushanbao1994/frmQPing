#include "qping.h"
#include <QProcess>
#include <QDebug>

QPing::QPing(const quint32 ip, int timerout, QObject *parent) : QObject(parent)
{
    m_ip = ip;                  // 目标IP
    m_timerout = timerout;      // 超时时间

    m_thread = new QThread(this);       // Ping所在的线程
    m_pingTh = new QPingThread(m_ip);   // Ping实例化
    // 设置参数 Ping->PingThread
    QObject::connect(this, &QPing::signal_setPingParameter,
                     m_pingTh, &QPingThread::slot_setPingParameter);
    // 执行命令 Ping->PingThread
    QObject::connect(this, &QPing::signal_executePingComman, m_pingTh,
                     &QPingThread::slot_executePingComman);
    // 返回结果 PingThread->Ping
    QObject::connect(m_pingTh, &QPingThread::signal_pingOk,
                     this, &QPing::slot_pingOk);

    m_pingTh->moveToThread(m_thread);
    m_thread->start();
}

// 设置参数（IP，超时时间）
void QPing::setPingParameter(const quint32 ip, int timerout)  // 设置参数
{
    // 发信号给Ping线程 设置参数
    emit signal_setPingParameter(ip, timerout);
}
// 执行Ping操作
void QPing::executePingComman()
{
    // 发信号给Ping线程 执行命令
    emit signal_executePingComman();
}

// 接收Ping线程返回的结果
void QPing::slot_pingOk(quint32 ip, int s)     // Ping OK
{
    // 收到Ping线程的结果后，发信号给使用者 执行结果
    emit signal_pingOk(ip, s);
}
