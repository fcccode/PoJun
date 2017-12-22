#include "PoJunUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PoJunUI pj; 
    pj.showMaximized();
    pj.setWindowState(Qt::WindowMaximized);
    return a.exec();
}
