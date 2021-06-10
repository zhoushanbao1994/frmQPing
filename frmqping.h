#ifndef FRMQPING_H
#define FRMQPING_H

#include <QDialog>
#include "qping.h"
#include <QTimer>
#include "lightbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class frmQPing; }
QT_END_NAMESPACE

class frmQPing : public QDialog
{
    Q_OBJECT

public:
    frmQPing(QWidget *parent = nullptr);
    ~frmQPing();
private:
    void UiInit();
    void start();
    void stop();

private slots:
    void TimerOut();
    void PingResult(quint32 ip, quint32 id, int s,
                    quint32 timeOutConut, quint32 pingCount);      // Ping结果
    void on_pushButton_clicked();

private:
    Ui::frmQPing *ui;

    QTimer *m_timer;
    quint32 m_timerCount = 0;
    QVector<QPing *> m_ping;
    QVector<LightButton *>m_pLightButton;       // 状态指示灯

    int m_tim;              // 定时间隔
    quint32 m_startAddr;    // 开始IP
    quint32 m_endAddr;      // 终止IP
    quint32 m_countAddr = 0;// IP计数，一共多少个IP

    bool m_bIsRun = false;
};
#endif // FRMQPING_H
