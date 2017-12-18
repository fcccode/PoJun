#include "XOutPutWindow.h"


XOutPutWindow::XOutPutWindow(QWidget *parent)
    : QDockWidget(parent)
{
    opw.setupUi(this);

    opw.vlayout->setMargin(0);
    opw.vlayout->setSpacing(2);

    opw.hlayout->setMargin(3);
    opw.hlayout->setSpacing(3);

    opw.widget->setLayout(opw.vlayout);

    opw.input->setFocus();
}


XOutPutWindow::~XOutPutWindow()
{
}
