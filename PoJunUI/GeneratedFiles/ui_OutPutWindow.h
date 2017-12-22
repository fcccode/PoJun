/********************************************************************************
** Form generated from reading UI file 'OutPutWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTPUTWINDOW_H
#define UI_OUTPUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutPutWindow
{
public:
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vlayout;
    QTextEdit *show_text;

    void setupUi(QDockWidget *OutPutWindow)
    {
        if (OutPutWindow->objectName().isEmpty())
            OutPutWindow->setObjectName(QStringLiteral("OutPutWindow"));
        OutPutWindow->resize(704, 502);
        widget = new QWidget();
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayoutWidget = new QWidget(widget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 701, 481));
        vlayout = new QVBoxLayout(verticalLayoutWidget);
        vlayout->setObjectName(QStringLiteral("vlayout"));
        vlayout->setContentsMargins(0, 0, 0, 6);
        show_text = new QTextEdit(verticalLayoutWidget);
        show_text->setObjectName(QStringLiteral("show_text"));
        show_text->setReadOnly(true);

        vlayout->addWidget(show_text);

        OutPutWindow->setWidget(widget);

        retranslateUi(OutPutWindow);

        QMetaObject::connectSlotsByName(OutPutWindow);
    } // setupUi

    void retranslateUi(QDockWidget *OutPutWindow)
    {
        OutPutWindow->setWindowTitle(QApplication::translate("OutPutWindow", "\350\276\223\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OutPutWindow: public Ui_OutPutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTPUTWINDOW_H
