#include "XOutPutWindow.h"


XOutPutWindow::XOutPutWindow(QWidget *parent)
    : QDockWidget(parent)
{
    opw.setupUi(this);
    opw.widget->setLayout(opw.vlayout); 
    opw.input->setFocus(); 
}


XOutPutWindow::~XOutPutWindow()
{
}

void XOutPutWindow::on_OutPutWindow_visibilityChanged(bool visible)
{
    int i = 0;
}