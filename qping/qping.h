#ifndef QPING_H
#define QPING_H

#include <QObject>
#include <QThread>
#include "qpingthread.h"


class QPing : public QObject
{
    Q_OBJECT

    /**************************************************************************************/
    /*************************************** 对外 ******************************************/
public:
    explicit QPing(const quint32 ip, int timerout = 1000, QObject *parent = nullptr);

    // 设置参数（IP，超时时间）
    void setPingParameter(const quint32 ip, int timerout = 1000);  // 设置参数
    // 执行Ping操作
    void executePingComman();

signals: //信号
    void signal_pingOk(quint32 ip, int);     // Ping的结果, 发给调用者
    /*************************************** 对外 ******************************************/
    /**************************************************************************************/
    /**************************************************************************************/
    /*************************************** 对内 ******************************************/
signals:        //信号 发给Ping线程的信号
    void signal_setPingParameter(const quint32 ip, int timerout = 1000);  // 设置参数
    void signal_executePingComman();

public slots:  // 槽  接收Ping线程的槽
    void slot_pingOk(quint32 ip, int);     // 接收Ping线程返回的结果
    /*************************************** 对内 ******************************************/
    /**************************************************************************************/

private:
   quint32 m_ip;            // 要Ping的IP地址
   QString m_timerout;      // 超时时间

   QThread *m_thread;       // Ping工作的线程
   QPingThread *m_pingTh;   // Ping实例化
};

#endif // QPING_H
