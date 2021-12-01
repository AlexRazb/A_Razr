/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QWidget *centralwidget;
    QCheckBox *CB1;
    QCheckBox *CB2;
    QCheckBox *CB3;
    QCheckBox *CBA;
    QLabel *label;
    QFrame *line;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QFrame *line_2;
    QPushButton *pushButton;
    QCheckBox *CBZakrep;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(265, 159);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action->setMenuRole(QAction::AboutRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        CB1 = new QCheckBox(centralwidget);
        CB1->setObjectName(QString::fromUtf8("CB1"));
        CB1->setGeometry(QRect(20, 40, 50, 50));
        CB2 = new QCheckBox(centralwidget);
        CB2->setObjectName(QString::fromUtf8("CB2"));
        CB2->setGeometry(QRect(80, 40, 50, 50));
        CB3 = new QCheckBox(centralwidget);
        CB3->setObjectName(QString::fromUtf8("CB3"));
        CB3->setGeometry(QRect(140, 40, 50, 50));
        CBA = new QCheckBox(centralwidget);
        CBA->setObjectName(QString::fromUtf8("CBA"));
        CBA->setGeometry(QRect(200, 40, 50, 50));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 0, 31, 21));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 20, 491, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 0, 31, 21));
        label_2->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 0, 31, 21));
        label_3->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 0, 31, 21));
        label_4->setFont(font);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(-10, 90, 491, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 100, 101, 35));
        QIcon icon;
        icon.addFile(QString::fromUtf8("pics/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(25, 25));
        CBZakrep = new QCheckBox(centralwidget);
        CBZakrep->setObjectName(QString::fromUtf8("CBZakrep"));
        CBZakrep->setGeometry(QRect(130, 110, 81, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 265, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\237\320\236 \320\264\320\273\321\217 \321\200\320\260\320\267\321\200\321\213\320\262\320\260 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217", nullptr));
        action->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        CB1->setText(QApplication::translate("MainWindow", "1", nullptr));
        CB2->setText(QApplication::translate("MainWindow", "2", nullptr));
        CB3->setText(QApplication::translate("MainWindow", "3", nullptr));
        CBA->setText(QApplication::translate("MainWindow", "\320\222\321\201\320\265", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\222\321\201\320\265 ", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "1", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "2", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "3", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265", nullptr));
        CBZakrep->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\320\265\320\277\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
