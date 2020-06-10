#ifndef QPINGTHREAD_H
#define QPINGTHREAD_H

#include <QObject>
#include <QThread>
#include <QHostAddress>

class QPingThread : public QObject
{
    Q_OBJECT
public:
    explicit QPingThread(const quint32 ip, int timerout = 1000, QObject *parent = nullptr);

signals: //信号
    void signal_pingOk(quint32 ip, int);     // Ping OK

public slots:  // 槽 （与外部通讯相关）
    void slot_setPingParameter(const quint32 ip, int timerout = 1000);  // 设置参数
    void slot_executePingComman();

private:
    quint32 m_ip;
    int m_timerout;
};

#endif // QPINGTHREAD_H
