#define PINOUT3   3//D3
#define PINOUT5   5//D5
#define PINOUT9   9//D9


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(PINOUT3, OUTPUT);
  pinMode(PINOUT5, OUTPUT);
  pinMode(PINOUT9, OUTPUT);

  //Включить все выходы
     SetAllPinsState(1);
  //

  Connect();
  getPinsStatus();//получить состояние пинов
}

void loop() {

  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
  int data = Serial.read() - '0';

    if (data == 0)/*pin3 ON*/
    {  
     digitalWrite(PINOUT3, HIGH);
     getPinsStatus();//вывести состояние пинов
    }
    if (data == 1)/*pin3 OFF*/
    {  
     digitalWrite(PINOUT3, LOW);
     getPinsStatus();//вывести состояние пинов
    }
    if (data == 2)/*pin5 ON*/
    {  
     digitalWrite(PINOUT5, HIGH);
     getPinsStatus();//вывести состояние пинов
    }
    if (data == 3)/*pin5 OFF*/
    {  
     digitalWrite(PINOUT5, LOW);
     getPinsStatus();//вывести состояние пинов
    }
    if (data == 4)/*pin9 ON*/
    {  
     digitalWrite(PINOUT9, HIGH);
     getPinsStatus();//вывести состояние пинов
    }
    if (data == 5)/*pin9 OFF*/
    {  
     digitalWrite(PINOUT9, LOW);
     getPinsStatus();//вывести состояние пинов
    }
    if (data == 6)/*ALL pins ON*/
    {  
      SetAllPinsState(1);
      getPinsStatus();//вывести состояние пинов
    }
    if (data == 7)/*ALL pins OFF*/
    {  
      SetAllPinsState(0);
      getPinsStatus();//вывести состояние пинов
    }
    if (data == 8)/*get pins status*/
    {    
      /**/ getPinsStatus();//вывести состояние пинов
    }
    /*Выдает в ком сообщ для переподключения*/
    if (data == 9)//
    {
      Connect();
      getPinsStatus();//вывести состояние пинов
    }

    /***************************************************/
    if ((data == 56) || (data == 24))//h or H
    {
      //помощь 
      helpInfo();
    }
    /***************************************************/
  }
  
}

/*Для проверки соединения*/
void Connect()
{
  //getPinsStatus();//получить состояние пинов
  //Serial.println("OK");//выдает после получения ответа
  /***/
  for(;;)
  {
    Serial.println("Ready?Wait Y\n\rReady?Wait Y\n\rReady?Wait Y");//выдает в порт
    //Serial.println("Ready?Wait Y");//выдает в порт
    if(Serial.find("Y")) break;
  }

}

/*Задать значение всем пинам*/
void SetAllPinsState(int State)
{
 digitalWrite(PINOUT3, State);
 digitalWrite(PINOUT5, State);
 digitalWrite(PINOUT9, State);

}

void getPinsStatus()
{
  int stat3 = 0,
      stat5 = 0,
      stat9 = 0;
  
      if (digitalRead(PINOUT3)) stat3 = 0x1;
      if (digitalRead(PINOUT5)) stat5 = 0x1 << 1;
      if (digitalRead(PINOUT9)) stat9 = 0x1 << 2;
      
      //Serial.print("0x");
      Serial.print(stat3 + stat5 + stat9, HEX); 
      Serial.print(" : ");
      Serial.print("1Ch");
      if(stat3) Serial.print("_ON  "); 
      else Serial.print("_OFF ");  
      Serial.print("2Ch");
      if(stat5) Serial.print("_ON  "); 
      else Serial.print("_OFF ");   
      Serial.print("3Ch"); 
      if(stat9) Serial.println("_ON "); 
      else Serial.println("_OFF");             
}

void helpInfo()
{
  Serial.print("\n\r");
  Serial.print("0 - connection 1 ON\n\r");
  Serial.print("1 - connection 1 OFF\n\r");
  Serial.print("2 - connection 2 ON\n\r");
  Serial.print("3 - connection 2 OFF\n\r");
  Serial.print("4 - connection 3 ON\n\r");
  Serial.print("5 - connection 3 OFF\n\r");
  Serial.print("6 - ALL connection ON\n\r");
  Serial.print("7 - ALL connection OFF\n\r");
  Serial.print("8 - get pins status\n\r");
  Serial.print("9 - imit start programm\n\r");
  Serial.print("h or H - help\n\r");
  
}
