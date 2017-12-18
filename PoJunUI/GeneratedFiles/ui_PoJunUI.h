/********************************************************************************
** Form generated from reading UI file 'PoJunUI.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POJUNUI_H
#define UI_POJUNUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PoJunUIClass
{
public:
    QAction *ma_open;
    QAction *ma_attached;
    QAction *ma_quit;
    QAction *ma_disconnect;
    QAction *ma_module;
    QAction *ma_memory;
    QAction *ma_thread;
    QAction *action_6;
    QAction *ma_handle;
    QAction *ma_she;
    QAction *ma_run;
    QAction *ma_stop;
    QAction *ma_restart;
    QAction *ma_close;
    QAction *ma_step_into;
    QAction *ma_step_by_step;
    QAction *ma_auto_enter;
    QAction *ma_auto_step_over;
    QAction *ma_exec_ret;
    QAction *ma_exec_user;
    QAction *ma_select_import;
    QAction *ma_load_symbol;
    QAction *tb4;
    QAction *ma_help;
    QAction *ma_about;
    QAction *ma_set;
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QMenuBar *menu_bar;
    QMenu *mb_file;
    QMenu *mb_view;
    QMenu *mb_debug;
    QMenu *mb_option;
    QMenu *mb_help;
    QMenu *mb_plug;
    QMenu *mb_cut;

    void setupUi(QMainWindow *PoJunUIClass)
    {
        if (PoJunUIClass->objectName().isEmpty())
            PoJunUIClass->setObjectName(QStringLiteral("PoJunUIClass"));
        PoJunUIClass->resize(800, 600);
        ma_open = new QAction(PoJunUIClass);
        ma_open->setObjectName(QStringLiteral("ma_open"));
        ma_attached = new QAction(PoJunUIClass);
        ma_attached->setObjectName(QStringLiteral("ma_attached"));
        ma_quit = new QAction(PoJunUIClass);
        ma_quit->setObjectName(QStringLiteral("ma_quit"));
        ma_disconnect = new QAction(PoJunUIClass);
        ma_disconnect->setObjectName(QStringLiteral("ma_disconnect"));
        ma_module = new QAction(PoJunUIClass);
        ma_module->setObjectName(QStringLiteral("ma_module"));
        ma_memory = new QAction(PoJunUIClass);
        ma_memory->setObjectName(QStringLiteral("ma_memory"));
        ma_thread = new QAction(PoJunUIClass);
        ma_thread->setObjectName(QStringLiteral("ma_thread"));
        action_6 = new QAction(PoJunUIClass);
        action_6->setObjectName(QStringLiteral("action_6"));
        ma_handle = new QAction(PoJunUIClass);
        ma_handle->setObjectName(QStringLiteral("ma_handle"));
        ma_she = new QAction(PoJunUIClass);
        ma_she->setObjectName(QStringLiteral("ma_she"));
        ma_run = new QAction(PoJunUIClass);
        ma_run->setObjectName(QStringLiteral("ma_run"));
        ma_stop = new QAction(PoJunUIClass);
        ma_stop->setObjectName(QStringLiteral("ma_stop"));
        ma_restart = new QAction(PoJunUIClass);
        ma_restart->setObjectName(QStringLiteral("ma_restart"));
        ma_close = new QAction(PoJunUIClass);
        ma_close->setObjectName(QStringLiteral("ma_close"));
        ma_step_into = new QAction(PoJunUIClass);
        ma_step_into->setObjectName(QStringLiteral("ma_step_into"));
        ma_step_by_step = new QAction(PoJunUIClass);
        ma_step_by_step->setObjectName(QStringLiteral("ma_step_by_step"));
        ma_auto_enter = new QAction(PoJunUIClass);
        ma_auto_enter->setObjectName(QStringLiteral("ma_auto_enter"));
        ma_auto_step_over = new QAction(PoJunUIClass);
        ma_auto_step_over->setObjectName(QStringLiteral("ma_auto_step_over"));
        ma_exec_ret = new QAction(PoJunUIClass);
        ma_exec_ret->setObjectName(QStringLiteral("ma_exec_ret"));
        ma_exec_user = new QAction(PoJunUIClass);
        ma_exec_user->setObjectName(QStringLiteral("ma_exec_user"));
        ma_select_import = new QAction(PoJunUIClass);
        ma_select_import->setObjectName(QStringLiteral("ma_select_import"));
        ma_load_symbol = new QAction(PoJunUIClass);
        ma_load_symbol->setObjectName(QStringLiteral("ma_load_symbol"));
        tb4 = new QAction(PoJunUIClass);
        tb4->setObjectName(QStringLiteral("tb4"));
        ma_help = new QAction(PoJunUIClass);
        ma_help->setObjectName(QStringLiteral("ma_help"));
        ma_about = new QAction(PoJunUIClass);
        ma_about->setObjectName(QStringLiteral("ma_about"));
        ma_set = new QAction(PoJunUIClass);
        ma_set->setObjectName(QStringLiteral("ma_set"));
        centralWidget = new QWidget(PoJunUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PoJunUIClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(PoJunUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PoJunUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        menu_bar = new QMenuBar(PoJunUIClass);
        menu_bar->setObjectName(QStringLiteral("menu_bar"));
        menu_bar->setGeometry(QRect(0, 0, 800, 23));
        mb_file = new QMenu(menu_bar);
        mb_file->setObjectName(QStringLiteral("mb_file"));
        mb_view = new QMenu(menu_bar);
        mb_view->setObjectName(QStringLiteral("mb_view"));
        mb_debug = new QMenu(menu_bar);
        mb_debug->setObjectName(QStringLiteral("mb_debug"));
        mb_option = new QMenu(menu_bar);
        mb_option->setObjectName(QStringLiteral("mb_option"));
        mb_help = new QMenu(menu_bar);
        mb_help->setObjectName(QStringLiteral("mb_help"));
        mb_plug = new QMenu(menu_bar);
        mb_plug->setObjectName(QStringLiteral("mb_plug"));
        mb_cut = new QMenu(menu_bar);
        mb_cut->setObjectName(QStringLiteral("mb_cut"));
        PoJunUIClass->setMenuBar(menu_bar);

        menu_bar->addAction(mb_file->menuAction());
        menu_bar->addAction(mb_view->menuAction());
        menu_bar->addAction(mb_debug->menuAction());
        menu_bar->addAction(mb_option->menuAction());
        menu_bar->addAction(mb_help->menuAction());
        menu_bar->addAction(mb_cut->menuAction());
        menu_bar->addAction(mb_plug->menuAction());
        mb_file->addAction(ma_open);
        mb_file->addAction(ma_attached);
        mb_file->addAction(ma_disconnect);
        mb_file->addAction(ma_quit);
        mb_file->addSeparator();
        mb_view->addAction(ma_module);
        mb_view->addAction(ma_memory);
        mb_view->addAction(ma_thread);
        mb_view->addAction(ma_handle);
        mb_view->addAction(ma_she);
        mb_debug->addAction(ma_run);
        mb_debug->addAction(ma_stop);
        mb_debug->addAction(ma_restart);
        mb_debug->addAction(ma_close);
        mb_debug->addSeparator();
        mb_debug->addAction(ma_step_into);
        mb_debug->addAction(ma_step_by_step);
        mb_debug->addAction(ma_auto_enter);
        mb_debug->addAction(ma_auto_step_over);
        mb_debug->addAction(ma_exec_ret);
        mb_debug->addAction(ma_exec_user);
        mb_debug->addSeparator();
        mb_debug->addAction(ma_select_import);
        mb_debug->addAction(ma_load_symbol);
        mb_option->addAction(ma_set);
        mb_help->addAction(ma_help);
        mb_help->addAction(ma_about);

        retranslateUi(PoJunUIClass);

        QMetaObject::connectSlotsByName(PoJunUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *PoJunUIClass)
    {
        PoJunUIClass->setWindowTitle(QApplication::translate("PoJunUIClass", "\347\240\264\345\206\233", Q_NULLPTR));
        ma_open->setText(QApplication::translate("PoJunUIClass", "\346\211\223\345\274\200\345\217\257\346\211\247\350\241\214\346\226\207\344\273\266", Q_NULLPTR));
        ma_open->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+O", Q_NULLPTR));
        ma_attached->setText(QApplication::translate("PoJunUIClass", "\351\231\204\345\212\240\345\210\260\350\277\233\347\250\213", Q_NULLPTR));
        ma_attached->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+A", Q_NULLPTR));
        ma_quit->setText(QApplication::translate("PoJunUIClass", "\351\200\200\345\207\272(\351\200\200\345\207\272\350\277\233\347\250\213)", Q_NULLPTR));
        ma_quit->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+Q", Q_NULLPTR));
        ma_disconnect->setText(QApplication::translate("PoJunUIClass", "\346\226\255\345\274\200(\344\270\215\351\200\200\345\207\272\350\277\233\347\250\213)", Q_NULLPTR));
        ma_disconnect->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+B", Q_NULLPTR));
        ma_module->setText(QApplication::translate("PoJunUIClass", "\346\250\241\345\235\227", Q_NULLPTR));
        ma_module->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+E", Q_NULLPTR));
        ma_memory->setText(QApplication::translate("PoJunUIClass", "\345\206\205\345\255\230", Q_NULLPTR));
        ma_memory->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+M", Q_NULLPTR));
        ma_thread->setText(QApplication::translate("PoJunUIClass", "\347\272\277\347\250\213", Q_NULLPTR));
        ma_thread->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+T", Q_NULLPTR));
        action_6->setText(QApplication::translate("PoJunUIClass", "\347\252\227\345\217\243", Q_NULLPTR));
        ma_handle->setText(QApplication::translate("PoJunUIClass", "\345\217\245\346\237\204", Q_NULLPTR));
        ma_handle->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+H", Q_NULLPTR));
        ma_she->setText(QApplication::translate("PoJunUIClass", "SHE\351\223\276", Q_NULLPTR));
        ma_she->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+S", Q_NULLPTR));
        ma_run->setText(QApplication::translate("PoJunUIClass", "\350\277\220\350\241\214", Q_NULLPTR));
        ma_run->setShortcut(QApplication::translate("PoJunUIClass", "F9", Q_NULLPTR));
        ma_stop->setText(QApplication::translate("PoJunUIClass", "\346\232\202\345\201\234", Q_NULLPTR));
        ma_stop->setShortcut(QApplication::translate("PoJunUIClass", "F12", Q_NULLPTR));
        ma_restart->setText(QApplication::translate("PoJunUIClass", "\351\207\215\346\226\260\345\274\200\345\247\213", Q_NULLPTR));
        ma_restart->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+F12", Q_NULLPTR));
        ma_close->setText(QApplication::translate("PoJunUIClass", "\345\205\263\351\227\255\347\250\213\345\272\217", Q_NULLPTR));
        ma_close->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+F11", Q_NULLPTR));
        ma_step_into->setText(QApplication::translate("PoJunUIClass", "\345\215\225\346\255\245\346\255\245\345\205\245", Q_NULLPTR));
        ma_step_into->setShortcut(QApplication::translate("PoJunUIClass", "F7", Q_NULLPTR));
        ma_step_by_step->setText(QApplication::translate("PoJunUIClass", "\345\215\225\346\255\245\346\255\245\350\277\207", Q_NULLPTR));
        ma_step_by_step->setShortcut(QApplication::translate("PoJunUIClass", "F8", Q_NULLPTR));
        ma_auto_enter->setText(QApplication::translate("PoJunUIClass", "\350\207\252\345\212\250\346\255\245\345\205\245", Q_NULLPTR));
        ma_auto_enter->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+F7", Q_NULLPTR));
        ma_auto_step_over->setText(QApplication::translate("PoJunUIClass", "\350\207\252\345\212\250\346\255\245\350\277\207", Q_NULLPTR));
        ma_auto_step_over->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+F8", Q_NULLPTR));
        ma_exec_ret->setText(QApplication::translate("PoJunUIClass", "\346\211\247\350\241\214\345\210\260\350\277\224\345\233\236\346\214\207\344\273\244", Q_NULLPTR));
        ma_exec_ret->setShortcut(QApplication::translate("PoJunUIClass", "Ctrl+F9", Q_NULLPTR));
        ma_exec_user->setText(QApplication::translate("PoJunUIClass", "\346\211\247\350\241\214\345\210\260\347\224\250\346\210\267\344\273\243\347\240\201", Q_NULLPTR));
        ma_exec_user->setShortcut(QApplication::translate("PoJunUIClass", "Alt+F9", Q_NULLPTR));
        ma_select_import->setText(QApplication::translate("PoJunUIClass", "\351\200\211\346\213\251\345\257\274\345\205\245\345\272\223", Q_NULLPTR));
        ma_load_symbol->setText(QApplication::translate("PoJunUIClass", "\345\212\240\350\275\275\347\254\246\345\217\267", Q_NULLPTR));
        tb4->setText(QApplication::translate("PoJunUIClass", "\350\256\276\347\275\256", Q_NULLPTR));
        ma_help->setText(QApplication::translate("PoJunUIClass", "\345\270\256\345\212\251", Q_NULLPTR));
        ma_about->setText(QApplication::translate("PoJunUIClass", "\345\205\263\344\272\216", Q_NULLPTR));
        ma_set->setText(QApplication::translate("PoJunUIClass", "\350\256\276\347\275\256", Q_NULLPTR));
        mb_file->setTitle(QApplication::translate("PoJunUIClass", "\346\226\207\344\273\266(&F)", Q_NULLPTR));
        mb_view->setTitle(QApplication::translate("PoJunUIClass", "\350\247\206\345\233\276(&V)", Q_NULLPTR));
        mb_debug->setTitle(QApplication::translate("PoJunUIClass", "\350\260\203\350\257\225(&D)", Q_NULLPTR));
        mb_option->setTitle(QApplication::translate("PoJunUIClass", "\351\200\211\351\241\271(&O)", Q_NULLPTR));
        mb_help->setTitle(QApplication::translate("PoJunUIClass", "\345\270\256\345\212\251(&H)", Q_NULLPTR));
        mb_plug->setTitle(QApplication::translate("PoJunUIClass", "\346\217\222\344\273\266(&P)", Q_NULLPTR));
        mb_cut->setTitle(QApplication::translate("PoJunUIClass", "|", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PoJunUIClass: public Ui_PoJunUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POJUNUI_H
