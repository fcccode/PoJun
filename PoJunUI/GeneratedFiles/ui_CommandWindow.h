/********************************************************************************
** Form generated from reading UI file 'CommandWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDWINDOW_H
#define UI_COMMANDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommandWindow
{
public:
    QWidget *dockWidgetContents;
    QWidget *layoutWidget;
    QHBoxLayout *hlayout;
    QLabel *command;
    QLineEdit *input;

    void setupUi(QDockWidget *CommandWindow)
    {
        if (CommandWindow->objectName().isEmpty())
            CommandWindow->setObjectName(QStringLiteral("CommandWindow"));
        CommandWindow->resize(703, 46);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        layoutWidget = new QWidget(dockWidgetContents);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(4, 0, 691, 22));
        hlayout = new QHBoxLayout(layoutWidget);
        hlayout->setObjectName(QStringLiteral("hlayout"));
        hlayout->setContentsMargins(6, 0, 6, 0);
        command = new QLabel(layoutWidget);
        command->setObjectName(QStringLiteral("command"));

        hlayout->addWidget(command);

        input = new QLineEdit(layoutWidget);
        input->setObjectName(QStringLiteral("input"));

        hlayout->addWidget(input);

        CommandWindow->setWidget(dockWidgetContents);

        retranslateUi(CommandWindow);

        QMetaObject::connectSlotsByName(CommandWindow);
    } // setupUi

    void retranslateUi(QDockWidget *CommandWindow)
    {
        CommandWindow->setWindowTitle(QApplication::translate("CommandWindow", "\345\221\275\344\273\244\350\276\223\345\205\245\347\252\227\345\217\243", Q_NULLPTR));
        command->setText(QApplication::translate("CommandWindow", "\345\221\275\344\273\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CommandWindow: public Ui_CommandWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDWINDOW_H
