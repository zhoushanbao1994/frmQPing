#include "app.h"

App::App(QObject *parent) : QObject(parent)
{

}

QSettings App::settings("./conf.ini", QSettings::IniFormat);
