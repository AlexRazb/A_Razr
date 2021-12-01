#include "mainwindow.h"
#include "PowerConnection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //PowerConnection newConn;
    //bool helper;
    //helper = newConn.Connect();
    //newConn.SetAllConnectionsState(0);
    //newConn.SetAllConnectionsState(1);
    w.setWindowIcon(QIcon("pics/connect.png"));
    w.show();
    return a.exec();
}
