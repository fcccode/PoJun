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

void PoJunUI::on_ma_open_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_attached_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_disconnect_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_quit_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_out_view_triggered()
{
    this->out_put_window->show();
}

void PoJunUI::on_ma_module_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_memory_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_thread_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_handle_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_she_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_run_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_stop_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_restart_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_close_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_step_into_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_step_by_step_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_auto_enter_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_auto_step_over_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_exec_ret_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_exec_user_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_set_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_help_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}

void PoJunUI::on_ma_about_triggered()
{
    ::MessageBox(0, 0, 0, 0);
}