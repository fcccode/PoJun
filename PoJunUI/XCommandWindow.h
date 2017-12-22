#pragma once
#include <QtWidgets/QDockWidget>
#include "ui_CommandWindow.h" 

class XCommandWindow : public QDockWidget
{
    Q_OBJECT
public:
    XCommandWindow(QWidget *parent = Q_NULLPTR);
    ~XCommandWindow();

private:
    Ui::CommandWindow cw;
};

