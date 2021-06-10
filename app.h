#ifndef APP_H
#define APP_H

#include <QObject>
#include <QSettings>

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);

    static QSettings settings;

signals:

};

#endif // APP_H
