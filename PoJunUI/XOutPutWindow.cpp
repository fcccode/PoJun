#include "XOutPutWindow.h"


XOutPutWindow::XOutPutWindow(QWidget *parent)
    : QDockWidget(parent)
{
    opw.setupUi(this);
    opw.vlayout->setMargin(0);
    opw.vlayout->setSpacing(0);
    opw.widget->setLayout(opw.vlayout);
}


XOutPutWindow::~XOutPutWindow()
{
} 