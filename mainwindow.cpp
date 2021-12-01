#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PowerConnection.h"
#include <vector>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), PC(new PowerConnection)//, AllChStat(3,0)
{
    ui->setupUi(this);
   // Qt::WindowFlags = windowFlags();
    this->setWindowFlag(Qt::WindowMaximizeButtonHint,0);//убрать "на весь экран"
    //this->setWindowFlag(Qt::f)//добавить флаг запрета растягивания формы



    /*Подключение слотов*/
    connect(this,&MainWindow::Check1_Signal,PC,&PowerConnection::F_ChannStateSlot);//1 чекбокс
    connect(this,&MainWindow::Check2_Signal,PC,&PowerConnection::S_ChannStateSlot);//2 чекбокс
    connect(this,&MainWindow::Check3_Signal,PC,&PowerConnection::T_ChannStateSlot);//3 чекбокс
    connect(this,&MainWindow::CheckAll_Signal,PC,&PowerConnection::A_ChannStateSlot);//чекбокс все
    connect(PC,&PowerConnection::StatusBar,this,&MainWindow::SetStatusBar_Slot);//Передача сообзщения из статус бара

    /*Подключение картинок к чекбоксам*/
    ui->CB1->setStyleSheet("QCheckBox::indicator { width:50px; height: 50px;} QCheckBox::indicator::checked {image: url(pics/on.png);} QCheckBox::indicator::unchecked {image: url(pics/off.png);}");
    ui->CB2->setStyleSheet("QCheckBox::indicator { width:50px; height: 50px;} QCheckBox::indicator::checked {image: url(pics/on.png);} QCheckBox::indicator::unchecked {image: url(pics/off.png);}");
    ui->CB3->setStyleSheet("QCheckBox::indicator { width:50px; height: 50px;} QCheckBox::indicator::checked {image: url(pics/on.png);} QCheckBox::indicator::unchecked {image: url(pics/off.png);}");
    ui->CBA->setStyleSheet("QCheckBox::indicator { width:50px; height: 50px;} QCheckBox::indicator::checked {image: url(pics/on.png);} QCheckBox::indicator::unchecked {image: url(pics/off.png);}");
    this->setStyleSheet("background-color: white;");

    PC->Connect();

    if(PC->isConnect())
    {
        ui->CB1->setChecked(PC->getConnectionState(1));ui->CB1->setEnabled(1);
        ui->CB2->setChecked(PC->getConnectionState(2));ui->CB2->setEnabled(1);
        ui->CB3->setChecked(PC->getConnectionState(3));ui->CB3->setEnabled(1);
        if (ui->CB1->isChecked() && ui->CB2->isChecked() && ui->CB3->isChecked())//Если все вкл
        {
            ui->CBA->setChecked(1);//чб все подкл
            ui->CBA->setEnabled(1);
        }
        else
        {
            ui->CBA->setChecked(0);
        }
    }
    if(!PC->isConnect())//если нет соединения с устройством
    {

        ui->CB1->setEnabled(0); ui->CB1->setChecked(0);
        ui->CB2->setEnabled(0); ui->CB2->setChecked(0);
        ui->CB3->setEnabled(0); ui->CB3->setChecked(0);
        ui->CBA->setEnabled(0); ui->CBA->setChecked(0);
    }



}

MainWindow::~MainWindow()
{
    delete ui;
    delete PC;
}


void MainWindow::on_CB1_clicked()
{  
    ui->CBA->setChecked(ui->CB1->isChecked() && ui->CB2->isChecked() && ui->CB3->isChecked());
    QApplication::processEvents();//обновить гуи
    emit Check1_Signal(ui->CB1->isChecked());

    if(!PC->isConnect())
    {
        on_pushButton_clicked();//переподключение
    }

}


void MainWindow::on_CB2_clicked()
{
    ui->CBA->setChecked(ui->CB1->isChecked() && ui->CB2->isChecked() && ui->CB3->isChecked());
    QApplication::processEvents();//обновить гуи
    emit Check2_Signal(ui->CB2->isChecked());

    if(!PC->isConnect())
    {
        on_pushButton_clicked();//переподключение
    }

}


void MainWindow::on_CB3_clicked()
{
    ui->CBA->setChecked(ui->CB1->isChecked() && ui->CB2->isChecked() && ui->CB3->isChecked());
    QApplication::processEvents();//обновить гуи
    emit Check3_Signal(ui->CB3->isChecked());

    if(!PC->isConnect())
    {
        on_pushButton_clicked();//переподключение
    }


}


void MainWindow::on_CBA_clicked()
{
    bool state = ui->CBA->isChecked();
    ui->CB1->setChecked(state);//значение согласно соединению
    ui->CB2->setChecked(state);//
    ui->CB3->setChecked(state);//
    QApplication::processEvents();//обновить гуи
    emit CheckAll_Signal(state);

    if(!PC->isConnect())
    {
        on_pushButton_clicked();//переподключение
    }
}

//slots
void MainWindow::SetStatusBar_Slot(QString str)
{
    ui->statusbar->showMessage(str);//запись сообщения в статусбар
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);

    /*Отключить чекбоксы*/
    ui->CB1->setEnabled(0);
    ui->CB2->setEnabled(0);
    ui->CB3->setEnabled(0);
    ui->CBA->setEnabled(0);

    PC->Connect();

    if(PC->isConnect())
    {
        ui->CB1->setChecked(PC->getConnectionState(1));ui->CB1->setEnabled(1);
        ui->CB2->setChecked(PC->getConnectionState(2));ui->CB2->setEnabled(1);
        ui->CB3->setChecked(PC->getConnectionState(3));ui->CB3->setEnabled(1);
        if (ui->CB1->isChecked() && ui->CB2->isChecked() && ui->CB3->isChecked())//Если все вкл
        {
            ui->CBA->setChecked(1);//чб все подкл
            ui->CBA->setEnabled(1);
        }
        else
        {
            ui->CBA->setChecked(0);
        }
        /*Включить чекбоксы*/
        ui->CB1->setEnabled(1);
        ui->CB2->setEnabled(1);
        ui->CB3->setEnabled(1);
        ui->CBA->setEnabled(1);

    }
    if(!PC->isConnect())//если нет соединения с устройством
    {

        ui->CB1->setEnabled(0); ui->CB1->setChecked(0);
        ui->CB2->setEnabled(0); ui->CB2->setChecked(0);
        ui->CB3->setEnabled(0); ui->CB3->setChecked(0);
        ui->CBA->setEnabled(0); ui->CBA->setChecked(0);
    }


    ui->pushButton->setEnabled(true);
}


void MainWindow::on_CBZakrep_clicked()
{
    if(ui->CBZakrep->isChecked())
    {
        this->setWindowFlag(Qt::WindowStaysOnTopHint,1);
        show();
    }
    if(!ui->CBZakrep->isChecked())
    {
        this->setWindowFlag(Qt::WindowStaysOnTopHint,0);
        show();
    }
}

