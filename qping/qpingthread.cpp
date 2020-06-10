#include "qpingthread.h"
#include <QProcess>
#include <QDebug>

QPingThread::QPingThread(const quint32 ip, int timerout, QObject *parent) : QObject(parent)
{
    m_ip = ip;
    m_timerout = timerout;
}

void QPingThread::slot_setPingParameter(const quint32 ip, int timerout)  // 设置参数
{
    m_ip = ip;
    m_timerout = timerout;
}
void QPingThread::slot_executePingComman()
{
    // #Linux指令 "ping -s 1 -c 1 IP"
    //QString cmdstr = QString("ping -s 1 -c 1 %1")
    //      .arg(ip);

    // #Windows指令 "ping IP -n 1 -w 超时(ms)"

    // 转换IP的，获得字符串形式的IP
    QString strIp = QHostAddress(m_ip).toString();

    // 拼接指令
    QString cmdstr = QString("ping %1 -n 1 -w %2")
            .arg(strIp).arg(m_timerout);

    // 执行指令
    QProcess cmd;
    cmd.start(cmdstr);
    cmd.waitForReadyRead(1000);
    cmd.waitForFinished(1000);

    // 获取结果
    QString response = cmd.readAll();
    if (response.indexOf("TTL") == -1) {
        emit signal_pingOk(m_ip, 0);        // Ping超时，返回信号
    }
    else {
        emit signal_pingOk(m_ip, 1);        // Ping成功，返回信号
    }
}
