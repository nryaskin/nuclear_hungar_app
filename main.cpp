#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Qt Hello GL 2 Example");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    MainWindow w;
    w.show();

    return a.exec();
}
