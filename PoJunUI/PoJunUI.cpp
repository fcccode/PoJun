#include "PoJunUI.h"
#include <QBoxLayout.h>
#include "XControllerCenter.h"
#include <XFileDlg.h>

PoJunUI::PoJunUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 
    init_ui();  
    init_connect();
}
 
void PoJunUI::init_ui()
{
    QWidget* cw = takeCentralWidget();
    if (cw)
    {
        delete cw;
    }

    setDockNestingEnabled(true);
      
    out_put_window = new XOutPutWindow;
    if (out_put_window != nullptr)
    {
        addDockWidget(Qt::TopDockWidgetArea, out_put_window);
    }  

    command_input = new XCommandWindow;
    if (command_input != nullptr)
    {
        addDockWidget(Qt::BottomDockWidgetArea, command_input);
    }
     
    ui.mainToolBar->update();
}

void PoJunUI::init_connect()
{ 
    if (out_put_window)
    {
        connect(XControllerCenter::pins(), SIGNAL(show_asm()), out_put_window, SLOT(show_asm()));
        connect(XControllerCenter::pins(), SIGNAL(show_run_command()), out_put_window, SLOT(show_run_command()));
    } 

    if (out_put_window)
    {
        connect(XControllerCenter::pins(), SIGNAL(command_in()), command_input, SLOT(command_in()));
        connect(command_input, SIGNAL(run_command()), XControllerCenter::pins(), SIGNAL(run_command()));
    }
}
 
void PoJunUI::on_ma_open_triggered()
{
    XString file_path = XFileDlg::open_dlg(); 
    if (file_path.not_empty())
    {
        XControllerCenter::pins()->dbg_new_process(file_path);
    }
    else
    {
        ::MessageBox(nullptr, L"打开文件失败!", L"破军", MB_OK);
    }
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

void PoJunUI::on_in_view_triggered()
{
    this->command_input->show();
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