#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PoJunUI.h"  
#include "XOutPutWindow.h"
#include "XCommandWindow.h" 
#include <windows.h>

class PoJunUI : public QMainWindow
{
    Q_OBJECT

public:
    PoJunUI(QWidget *parent = Q_NULLPTR);

private:  
    void init_ui();

    void init_connect();

    //////////////////////////////////////////////////////////////////////////

private slots:  
    //文件菜单
    //打开新的进程
    void on_ma_open_triggered(); 
    //附加到进程
    void on_ma_attached_triggered();
    //断开
    void on_ma_disconnect_triggered();
    //退出
    void on_ma_quit_triggered();

    //视图
    //子视图
    //输出窗口
    void on_out_view_triggered();
    //命令输入窗口
    void on_in_view_triggered();

    //查看模块
    void on_ma_module_triggered();
    //查看内存
    void on_ma_memory_triggered();
    //查看线程
    void on_ma_thread_triggered();
    //查看句柄
    void on_ma_handle_triggered();
    //查看异常链表
    void on_ma_she_triggered();

    //调试
    //运行
    void on_ma_run_triggered();
    //暂停
    void on_ma_stop_triggered();
    //重新调试
    void on_ma_restart_triggered();
    //关闭当前调试（断链）
    void on_ma_close_triggered();
    //单步入
    void on_ma_step_into_triggered();
    //单步过
    void on_ma_step_by_step_triggered();
    //自动步入
    void on_ma_auto_enter_triggered();
    //自动步过
    void on_ma_auto_step_over_triggered();
    //执行到返回
    void on_ma_exec_ret_triggered();
    //执行到用户代码段
    void on_ma_exec_user_triggered();

    //选项
    //配置
    void on_ma_set_triggered();

    //帮助
    //帮助
    void on_ma_help_triggered();
    //关于
    void on_ma_about_triggered();
       
private:
    Ui::PoJunUIClass ui;   

    XOutPutWindow* out_put_window;
    XCommandWindow* command_input;
};