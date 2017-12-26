#pragma once 
#include <QtWidgets/QDockWidget>
#include "ui_OutPutWindow.h" 
#include <XPJCoreHead.h> 

class XOutPutWindow : public QDockWidget
{
    Q_OBJECT
public:
    XOutPutWindow(QWidget *parent = Q_NULLPTR);
    ~XOutPutWindow();

public slots:
    void show_asm();
    
    void show_run_command();

    void show_db(const BYTE* memory_byte, DWORD address);

    void show_dw(const BYTE* memory_byte, DWORD address);
     
    void show_dd(const BYTE* memory_byte, DWORD address);

private:
    Ui::OutPutWindow opw;
};

