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
    //�ļ��˵�
    //���µĽ���
    void on_ma_open_triggered(); 
    //���ӵ�����
    void on_ma_attached_triggered();
    //�Ͽ�
    void on_ma_disconnect_triggered();
    //�˳�
    void on_ma_quit_triggered();

    //��ͼ
    //����ͼ
    //�������
    void on_out_view_triggered();
    //�������봰��
    void on_in_view_triggered();

    //�鿴ģ��
    void on_ma_module_triggered();
    //�鿴�ڴ�
    void on_ma_memory_triggered();
    //�鿴�߳�
    void on_ma_thread_triggered();
    //�鿴���
    void on_ma_handle_triggered();
    //�鿴�쳣����
    void on_ma_she_triggered();

    //����
    //����
    void on_ma_run_triggered();
    //��ͣ
    void on_ma_stop_triggered();
    //���µ���
    void on_ma_restart_triggered();
    //�رյ�ǰ���ԣ�������
    void on_ma_close_triggered();
    //������
    void on_ma_step_into_triggered();
    //������
    void on_ma_step_by_step_triggered();
    //�Զ�����
    void on_ma_auto_enter_triggered();
    //�Զ�����
    void on_ma_auto_step_over_triggered();
    //ִ�е�����
    void on_ma_exec_ret_triggered();
    //ִ�е��û������
    void on_ma_exec_user_triggered();

    //ѡ��
    //����
    void on_ma_set_triggered();

    //����
    //����
    void on_ma_help_triggered();
    //����
    void on_ma_about_triggered();
       
private:
    Ui::PoJunUIClass ui;   

    XOutPutWindow* out_put_window;
    XCommandWindow* command_input;
};