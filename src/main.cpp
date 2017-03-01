#include "MainWindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("changeofpace");
    QApplication::setApplicationName("Simple Injector");

    MainWindow w;
    w.show();

    return a.exec();
}
