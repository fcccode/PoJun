#pragma once
#include <QtWidgets/QDockWidget>
#include "ui_CommandWindow.h" 
#include <windows.h>

class XCommandWindow : public QDockWidget
{
    Q_OBJECT
public:
    XCommandWindow(QWidget *parent = Q_NULLPTR);
    ~XCommandWindow();
     
    void init_ui();

    void init_lock();

signals:
    void run_command();

public slots:
    void command_in();

    void on_input_returnPressed();
      
private:
    Ui::CommandWindow cw; 

    bool dbg_command;
};