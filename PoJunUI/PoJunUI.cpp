#include "PoJunUI.h"
#include <QBoxLayout.h>

PoJunUI::PoJunUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 
    
    set_dock(); 

    init_ui();
}

void PoJunUI::set_dock()
{
    QWidget* cw = takeCentralWidget();
    if (cw)
    { 
        delete cw;
    }

    setDockNestingEnabled(true);
}

void PoJunUI::init_ui()
{ 
    out_put_window = new XOutPutWindow;
    if (out_put_window != nullptr)
    {
        addDockWidget(Qt::LeftDockWidgetArea, out_put_window);
    } 
}