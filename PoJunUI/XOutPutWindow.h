#pragma once 
#include <QtWidgets/QDockWidget>
#include "ui_OutPutWindow.h" 

class XOutPutWindow : public QDockWidget
{
    Q_OBJECT
public:
    XOutPutWindow(QWidget *parent = Q_NULLPTR);
    ~XOutPutWindow();

private:
    Ui::OutPutWindow opw;
};

