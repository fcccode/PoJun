#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PoJunUI.h"  
#include "XOutPutWindow.h"
  
class PoJunUI : public QMainWindow
{
    Q_OBJECT

public:
    PoJunUI(QWidget *parent = Q_NULLPTR);

private:
    void set_dock();

    void init_ui();

private:
    Ui::PoJunUIClass ui;   

    XOutPutWindow* out_put_window;
};