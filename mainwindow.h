#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <PowerConnection.h>
#include <vector>
//#include <QtGui>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PowerConnection *PC;
    void SetStatusBar(QString Str);//Вывод строки в статусбар
   // std::vector<bool> AllChStat;//состояние всех каналов

signals:
    void Check1_Signal(bool State);//1 чекбокс
    void Check2_Signal(bool State);//2 чекбокс
    void Check3_Signal(bool State);//3 чекбокс
    void CheckAll_Signal(bool State);//вкл/выкл все каналы

private slots:
    void on_CB1_clicked();
    void on_CB2_clicked();
    void on_CB3_clicked();
    void on_CBA_clicked();

    void on_pushButton_clicked();

    void on_CBZakrep_clicked();

public slots:
    void SetStatusBar_Slot(QString str);//запись в статусбар
};
#endif // MAINWINDOW_H
