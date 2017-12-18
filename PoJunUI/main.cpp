#include "PoJunUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PoJunUI w;
    w.show();
    return a.exec();
}
