#ifndef POWERCONNECTION_H
#define POWERCONNECTION_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <vector>


class PowerConnection : public QSerialPort
{
    Q_OBJECT
public:
    explicit PowerConnection(QObject *parent = nullptr);
    virtual ~PowerConnection();
    bool Connect();                                           //Соединение
    void Disconnect();                                        //Закончить соединение с устройством
    bool SetConnectionState(int ConnectionNum, bool State);   //задать состояние соединения..сложить состояние в контейнер класса
    bool SetAllConnectionsStates(bool State);                 //задать состояние всем соединениям одновременно..сложить состояние в контейнер класса
    bool isConnect();                                         //Есть ли соединение
    void getAllConnectionsStates(std::vector<bool> &ConnectionStates);          //получить состояние соединений из контейнера класса
    bool getConnectionState(int ConnectionNum);//получить состояние соединения из контейнера класса


protected:
    QString getDataLine();                                    //Прочесть строку(50 символов)
    QString getData();                                        //Получить данные от устройства
    bool setData(QString str);                                //Отправить данные на устройство
    bool findConnection();                  //поиск и проверка контрольных слов для соединения
    bool parseAllConnectionsStates();      //парсинг состояний всех соединений
    QString	m_CommPort;               //Comport name
    bool	m_bOpened;                 //Is opened?
    qint32	m_Baud;                    //Comport Baud
    QSerialPort::DataBits m_DataBits;  //Comport DataBits  (default 8)
    QSerialPort::Parity	m_Parity;      //Comport Parity    (default NoParity)
    QSerialPort::StopBits m_StopBits;  //Comport StopBits  (dafault OneStop)
    QSerialPort::FlowControl m_RtsCts; //Comport FlowControl
    std::vector<bool> ConnState;       //Состояние соединений

public slots:
    void F_ChannStateSlot(bool State);//изменить состояние 1го канала
    void S_ChannStateSlot(bool State);//изменить состояние 2го канала
    void T_ChannStateSlot(bool State);//изменить состояние 3го канала
    void A_ChannStateSlot(bool State);//изменить состояние всех каналов

signals:
    void StatusBar(QString str);//писать в статусбар окна
};

#endif // POWERCONNECTION_H
