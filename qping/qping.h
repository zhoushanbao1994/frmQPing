#ifndef QPING_H
#define QPING_H

#include <QObject>
#include <QThread>
#include "qpingthread.h"

typedef enum _ePingRunStatus {
    ePingRunInit = 0,   // 初始恢复状态
    ePingWaitResult     // 等待结果状态
} ePingRunStatus;

class QPing : public QObject
{
    Q_OBJECT

    /**************************************************************************************/
    /*************************************** 对外 ******************************************/
public:
    explicit QPing(const quint32 ip, const quint32 id = 0, int timerout = 1000, QObject *parent = nullptr);

    // 设置参数（IP，超时时间）
    void setPingParameter(const quint32 ip, const quint32 id = 0, int timerout = 1000);  // 设置参数
    // 执行Ping操作
    void executePingComman();

signals: //信号
    void signal_pingOk(quint32 ip, quint32 id, int s,
                       quint32 timeOutConut, quint32 pingCount);     // Ping的结果, 发给调用者
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
    quint32 m_id;            // id标号
    QString m_timerout;      // 超时时间

   QThread *m_thread;       // Ping工作的线程
   QPingThread *m_pingTh;   // Ping实例化
   ePingRunStatus m_ePingS; // Ping执行状态

   quint32 m_pingCount = 0;         // Ping总计数
   quint32 m_timeOutCount = 0;      // 超时计数
};

#endif // QPING_H
