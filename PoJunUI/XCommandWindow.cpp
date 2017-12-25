#include "XCommandWindow.h" 
#include <XString.h>
#include "XDateCenter.h"


XCommandWindow::XCommandWindow(QWidget *parent)
    : QDockWidget(parent)
{
    cw.setupUi(this);
    init_ui(); 
    init_lock();
    dbg_command = false;
}

void XCommandWindow::init_lock()
{
}

void XCommandWindow::init_ui()
{
    cw.dockWidgetContents->setLayout(cw.hlayout);
    cw.dockWidgetContents->setFixedHeight(25);
}

XCommandWindow::~XCommandWindow()
{
}

void XCommandWindow::command_in()
{
    dbg_command = true;
}

void XCommandWindow::on_input_returnPressed()
{ 
    XString command = cw.input->text().toStdString();
    XDateCenter::pins()->set_command(command);
    cw.input->setText("");
    if (!dbg_command)
    {
        emit run_command();
    }

    dbg_command = false;
}