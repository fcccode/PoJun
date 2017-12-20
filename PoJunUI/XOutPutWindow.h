#pragma once 
#include <QtWidgets/QDockWidget>
#include "ui_OutPutWindow.h" 

class XOutPutWindow : public QDockWidget
{
    Q_OBJECT
public:
    XOutPutWindow(QWidget *parent = Q_NULLPTR);
    ~XOutPutWindow();

private slots:
    void on_OutPutWindow_visibilityChanged(bool visible);

private:
    Ui::OutPutWindow opw;
};

