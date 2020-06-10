#ifndef FRMQPING_H
#define FRMQPING_H

#include <QDialog>
#include "qping.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class frmQPing; }
QT_END_NAMESPACE

class frmQPing : public QDialog
{
    Q_OBJECT

public:
    frmQPing(QWidget *parent = nullptr);
    ~frmQPing();

private slots:
    void on_pushButton_clicked();

private:
    Ui::frmQPing *ui;

    QTimer *m_timer;
    QPing *m_ping;

    int m_tim;              // 定时间隔
    quint32 m_startAddr;    // 开始IP
    quint32 m_endAddr;      // 终止IP
    quint32 m_ip;
};
#endif // FRMQPING_H
