#include "PowerConnection.h"
#include <vector>
#include <QTextCodec>
#include <QApplication>


using namespace std;

PowerConnection::PowerConnection(QObject *parent) : QSerialPort(parent)
{
        m_bOpened = false;
        m_Baud = 9600;
        m_DataBits = QSerialPort::Data8;
        m_Parity = QSerialPort::NoParity;
        m_StopBits = QSerialPort::OneStop;
        m_RtsCts = QSerialPort::NoFlowControl;
        //ConnState.push_back(0);//иниц состояний
        //ConnState.push_back(0);//иниц состояний
        //ConnState.push_back(0);//иниц состояний
        //в дальнейшем возможна замена на чтение реальных состоянией соединений.
        //.по умолчанию, если все исправно, то все соединения ВКЛ.

}

//PowerConnection::PowerConnection()
//   {
//      // m_bOpened = ComPort::isOpen();
//       m_Baud = 9600;
//       m_DataBits = QSerialPort::Data8;
//       m_Parity = QSerialPort::NoParity;
//       m_StopBits = QSerialPort::OneStop;
//       m_RtsCts = QSerialPort::NoFlowControl;
//   }

PowerConnection::~PowerConnection()
{
    Disconnect();
}

void PowerConnection::Disconnect()
{
    m_bOpened = false;//связь разорвана
    PowerConnection::close();
}

bool PowerConnection::isConnect()
{
    return m_bOpened;
}

QString PowerConnection::getData()
{
    int count = 0;//счетчик циклов считываний
    //Фильтр для перевода кодировок
    QTextCodec *codec = QTextCodec::codecForName("cp1251");

    QByteArray R;// = PowerConnection::readAll();

    //проверяет готовность к чтению и читает, макс время ожидание готовности 1200мсек
    //возможны проблемы в GUI, в основном потоке
    //тк устройсво безостановочно выдает информацию после сброса,
    //необходимо ограничить считывание 5 разами во избежании зависания
    while (PowerConnection::waitForReadyRead(2000) && count<5)// && serial.canReadLine())
   {
    R.append(PowerConnection::readAll());
    ++count;
   }

    QString Buf = codec->toUnicode(R);
    return Buf;
}

QString PowerConnection::getDataLine()//функция читает до 40 знаков в буф
{
    //Фильтр для перевода кодировок
    QTextCodec *codec = QTextCodec::codecForName("cp1251");

    QByteArray R;// = PowerConnection::read(50);

    //проверяет готовность к чтению и читает, макс время ожидание готовности 1200мсек
    //возможны проблемы в GUI, в основном потоке
    while (PowerConnection::waitForReadyRead(2000) && R.size()<40)//
   {
    R.append(PowerConnection::read(50));
   }

    QString Buf = codec->toUnicode(R);

    return Buf;
}


bool PowerConnection::setData(QString str)
{
    if(PowerConnection::write(str.toUtf8()) != -1)//если записаны без ошибок
    {
        return PowerConnection::waitForBytesWritten(2000);//подтверждение записи
    }
    else
    {
        m_bOpened = 0;
        return false;
    }
}

bool PowerConnection::findConnection()
{
    QString helper;
    QString isReady = "Ready?Wait Y";     //Слово выдаваемое устройством при первом запуске
           //isOK = "OK";                 //Слово на ответ от приложения
   // Если найдена контрольная строка
   // helper = PowerConnection::getData();
   // helper = PowerConnection::readLine(50);//прочесть строку до 50 символов
   // PowerConnection::readData(help,50);
   // setData("8");
    helper = getDataLine();
    if(helper.contains(isReady,Qt::CaseInsensitive))//слово от устройства найдено
    {
        PowerConnection::clear();//очистить буферы порта

        PowerConnection::setData("Y");//контрольное слово для ответа

        if(parseAllConnectionsStates())//считать ответ о состоянии каналов
        {
            m_bOpened = true;//связь с устройством установлена
            return true;
        }
        else
        {
            m_bOpened = 0;
            return false;//устройство не ответило о состоянии
        }
    }
    m_bOpened = 0;
    return false;//контрольная строка не найдена
}


bool PowerConnection::Connect()
{
    emit StatusBar("Подключение...");
    QApplication::processEvents();
    Disconnect();

    PowerConnection::setBaudRate(m_Baud);
    PowerConnection::setDataBits(m_DataBits);
    PowerConnection::setParity(m_Parity);
    PowerConnection::setStopBits(m_StopBits);
    PowerConnection::setFlowControl(m_RtsCts);

    //для каждого доступного имени порта

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       //задать имя для подключения
        if (info.description() == "USB Serial Port")//Только если виртуальный юсб-ком порт
        {
            m_CommPort = info.portName();
            PowerConnection::setPortName(m_CommPort);//name
            if(PowerConnection::open(QIODevice::ReadWrite))//открытие на запись и чтение
            {
                setData("9");//для повторного подключения
               // Если найдена контрольная строка
                if(PowerConnection::findConnection())
                {
                    emit StatusBar("Соединение установлено");
                    return true;//соединение произошло
                }
                else//если открыт другой свободный ком
                {
                    PowerConnection::close();
                }
            }
        }
    }
    m_CommPort.clear();//нет действительного имени для соединения
    emit StatusBar("Ошибка соединения");
    return false;//устройство не подключено, либо подключено на другом терминале
}



//соединить, отключить соединение//1..3
bool PowerConnection::SetConnectionState(int ConnectionNum, bool State)
{
    if(m_bOpened)//если соединение было установлено
    {
        QString data;//данные для отправки на устройство
        if((ConnectionNum == 1) && (State == 1)) data = "0";     //1канал 3пин +
        else if((ConnectionNum == 1) && (State == 0)) data = "1";//1канал 3пин -
        else if((ConnectionNum == 2) && (State == 1)) data = "2";//1канал 5пин +
        else if((ConnectionNum == 2) && (State == 0)) data = "3";//1канал 5пин -
        else if((ConnectionNum == 3) && (State == 1)) data = "4";//1канал 9пин +
        else if((ConnectionNum == 3) && (State == 0)) data = "5";//1канал 9пин -


        else
            {
                return false;// введено ошибочное значение
            }

        if (PowerConnection::setData(data))//1, если была запись
            {
                return parseAllConnectionsStates();//ok_обновить значения подключений
            }
        else
            {
              m_bOpened = 0;
              return false;  //если не записалось в порт
            }

    }
    else
    {
        m_bOpened = 0;
        return false;//нет соединения
    }
}

bool PowerConnection::SetAllConnectionsStates(bool State)
{
   if(m_bOpened)//если есть соединение
   {
       if(State)//если 1, то вкл все
       {
          PowerConnection::setData("6");
       }
        else  PowerConnection::setData("7");
      return parseAllConnectionsStates();
   }
   else
   {
       return false;//нет соединения
   }
}


bool PowerConnection::parseAllConnectionsStates()
{
        QString data;//данные в строке
        uint dataInt;//данные в инт
        bool res = 0;//результат перевода из строки в число - успех\нет
        ConnState.clear();//очистить перед обновлением

        data = getData();

        reverse(data.begin(),data.end());//перевернуть строку
        data = data[28];//считать нужное значение

        if(data.isEmpty()) return false;//если нечего читать
        dataInt = data.toUInt(&res,10);
        if(!res || dataInt > 0x7)
        {
            m_bOpened = 0;
            return false;//Если не удалось перевести значение или оно больше 0x7
        }

        ConnState.push_back(static_cast<bool>(dataInt & (0x1 << 0)));//получить состояние 1го соединения
        ConnState.push_back(static_cast<bool>(dataInt & (0x1 << 1)));//получить состояние 2го соединения
        ConnState.push_back(static_cast<bool>(dataInt & (0x1 << 2)));//получить состояние 3го соединения
        return true;
}

void PowerConnection::getAllConnectionsStates(vector<bool> &ConnectionStates)
{
    ConnectionStates.clear();
    ConnectionStates.push_back(ConnState[0]);
    ConnectionStates.push_back(ConnState[1]);
    ConnectionStates.push_back(ConnState[2]);
    int i=3;//для остановы(удалить)
}

//1-3
bool PowerConnection::getConnectionState(int ConnectionNum)
{
    if(ConnectionNum>=1 && ConnectionNum<=3)
        return ConnState[ConnectionNum-1];
    else
        return false;
}

//slots
void PowerConnection::A_ChannStateSlot(bool State)//all
{
    SetAllConnectionsStates(State);
}

void PowerConnection::F_ChannStateSlot(bool State)//first
{
    SetConnectionState(1, State);
}

void PowerConnection::S_ChannStateSlot(bool State)//second
{
    SetConnectionState(2, State);
}

void PowerConnection::T_ChannStateSlot(bool State)//third
{
    SetConnectionState(3, State);
}












