#include "XCommandWindow.h"


XCommandWindow::XCommandWindow(QWidget *parent)
    : QDockWidget(parent)
{
    cw.setupUi(this); 
    cw.dockWidgetContents->setLayout(cw.hlayout);
    cw.dockWidgetContents->setFixedHeight(25);
}


XCommandWindow::~XCommandWindow()
{
}
