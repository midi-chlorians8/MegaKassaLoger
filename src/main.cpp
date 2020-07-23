#include <Arduino.h>
#include <Definition.h>

//EEPROM
#include <Wire.h>
const byte rom = 0x50;    // Address of 24LC256 eeprom chip
int eeAddress = 100;
String EeAdrStr = "99999";
char EeAdrStrBuf[6]; // Промежуточный контейнер для значения ползунка по адресам перед передачей в массив байт
byte MyArrayData[6]; // Контейнер в который перейдёт массив сhar
byte ReadPolzunArr [sizeof MyArrayData]; //Массив для чтения ползун значения
//EEPROM
//                 1  2  3  4  5  6  7  8 9  10 11 12
int MonthArr[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

void setup() {
 
  // BT
  digitalWrite(resetPin, HIGH); delay(200); 

  pinMode(resetPin, OUTPUT);  // инициализируем цифровой пин в качестве выхода
  Serial3.begin(9600);delay(200);  Serial3.println(teststring);

  inputString.reserve(200);
  // BT
  Serial.begin(115200);  delay(200);//while(!Serial){}

  //Кнопки и счётчики срабатываний
  pinMode(Line1_PIN1,INPUT_PULLUP); pinMode(Line1_PIN2,INPUT_PULLUP);
  pinMode(Line2_PIN1,INPUT_PULLUP); pinMode(Line2_PIN2,INPUT_PULLUP);
  Serial.print(F("TimingButt1:"));Serial.print(L1TimingButt1);  Serial.print(F(" TimingButt2:"));Serial.println(L1TimingButt2);
  Serial.println();Serial.println();Serial.println();
  //Кнопки и счётчики срабатываний

  // RTC
  Serial.print(F("compiled: "));    Serial.print(__DATE__); Serial.println(__TIME__);
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();
  if (!Rtc.IsDateTimeValid()) 
    {
        if (Rtc.LastError() != 0)
        {
            // we have a communications error
            // see https://www.arduino.cc/en/Reference/WireEndTransmission for 
            // what the number means
            Serial.print("RTC communications error = ");
            Serial.println(Rtc.LastError());
        }
        else
        {
            // Common Causes:
            //    1) first time you ran and the device wasn't running yet
            //    2) the battery on the device is low or even missing

            Serial.println("RTC lost confidence in the DateTime!");

            // following line sets the RTC to the date & time this sketch was compiled
            // it will also reset the valid flag internally unless the Rtc device is
            // having an issue

            Rtc.SetDateTime(compiled);
        }
    }
  // RTC



  //ExtEEPROM2
  byte err;
  Serial.print (F("I read. "));
  // Первый прочитался
  err= readEEPROM (rom, 1, ReadPolzunArr, sizeof(ReadPolzunArr) );
  //Serial.print("Polzunok is:"); Serial.println ((char *) ReadPolzunArr);  // display to confirm 
  EeAdrStr=(char *) ReadPolzunArr;
  Serial.print(F("EeAdrStr(Polzunok) is:")); Serial.println (EeAdrStr);
  eeAddress=EeAdrStr.toInt();
  //ExtEEPROM2
}


void ObrabotkaOneSide(const byte NameLine,int8_t pin,int8_t pin2,uint16_t& Line_countToday,bool& CanReadBool,unsigned long& TimingButtFirst,unsigned long& TimingButtSecond,bool& OneZjmyakButFirst,bool& OneZjmyakButSecond,unsigned long& WaitObrabotkaButt, String& DataStr){ //Функция должна при нажатии последовательно кнопки 1, а затем кнопки 2 увеличить глобальный счётчик прохода в линии

 //static bool CanReadBool = true;
 
 //Ввод значений нажатия кнопки. Результат нажатия були OneZjmyakBut1 и OneZjmyakBut2 
 if(CanReadBool == true){ //Если разрешено читать кнопки
    if(digitalRead(pin) == 0){ // Если нажата кнопка 1
      if(OneZjmyakButFirst==false){
      TimingButtFirst=millis(); // Присвоить значение таймера в переменную
      //Serial.print("[pin]TimingButt1:");Serial.print("");Serial.print(" TimingButt2:");Serial.println();
      OneZjmyakButFirst=true;
      }
  }
    if(digitalRead(pin2) == 0){// Если нажата кнопка 2
      if(OneZjmyakButSecond==false){
      TimingButtSecond=millis(); // Присвоить значение таймера в переменную
      //Serial.print("[pin2]TimingButt1:");Serial.print("");Serial.print(" TimingButt2:");Serial.println();
      OneZjmyakButSecond=true;
    }
  }
 }                      //Если разрешено читать кнопки
 //Ввод значений нажатия кнопки. Результат нажатия були OneZjmyakBut1 и OneZjmyakBut2 
 
 //Обработка значений. Прибавка счётчика нажатий
   if(OneZjmyakButFirst==true && OneZjmyakButSecond == true){ 
   CanReadBool=false; // Запретить чтение кнопок
      //if( (TimingButt1-TimingButt2)<0  ){
        if( TimingButtFirst < TimingButtSecond  ){
        //Line_countToday++; //Serial.print(F("Proxod Dobavlen:")); Serial.print(F("TB1-TB2)<0 "));       Serial.print(NameLine); Serial.print(F("Line_countToday:"));        Serial.print(Line_countToday); Serial.print(" ");        Serial.print(MyDateTimeStr); Serial.println();
        // DataStr=String(NameLine) + " " + MyDateTimeStr  + " " + Line_countToday;  Serial.print("DataStr:");Serial.println(DataStr);
      
        // Формирование и запись последовательности данных в EEPROM 
        byte Line = NameLine;       Serial.print("MyLine:");Serial.println(Line);
        writeEEPROM (rom, eeAddress, Line);     eeAddress+=1;

        byte Day = byte( MyDateTimeStr.substring(3,5).toInt()  );  Serial.print("MyDay:");Serial.println(Day);
        writeEEPROM (rom, eeAddress, Day);      eeAddress+=1;
        byte Month=byte( MyDateTimeStr.substring(0,2).toInt()  );  Serial.print("MyMonth:");Serial.println(Month);
        writeEEPROM (rom, eeAddress, Month);    eeAddress+=1;
        byte Year = byte( MyDateTimeStr.substring(8,10).toInt());  Serial.print("MyYear:");Serial.println(Year);
        writeEEPROM (rom, eeAddress, Year);      eeAddress+=1;

        byte Hour = byte( MyDateTimeStr.substring(11,13).toInt()); Serial.print("MyHour:");Serial.println(Hour);
        writeEEPROM (rom, eeAddress, Hour);     eeAddress+=1;
        byte Min = byte( MyDateTimeStr.substring(14,16).toInt() );  Serial.print("MyMin:");Serial.println(Min);
        writeEEPROM (rom, eeAddress, Min);      eeAddress+=1;
        byte Sec = byte( MyDateTimeStr.substring(17,19).toInt() );  Serial.print("MySec:");Serial.println(Sec);     
        writeEEPROM (rom, eeAddress, Sec);      eeAddress+=1;
        
        // И далее записываем в eeprom ячейку 1 значение ползунка в конце записи
        EeAdrStr=String(eeAddress);
        char EeAdrStrBuf[6];  EeAdrStr.toCharArray(EeAdrStrBuf, 6);
        for (int i=0; i < sizeof(MyArrayData); i++) { MyArrayData[i] = byte(EeAdrStrBuf[i] ); } //Преобразование массива сhar в массив byte
       
        writeEEPROM (rom, 1, MyArrayData, sizeof(MyArrayData) );  Serial.print("I write to eeprom Polzunok val:");Serial.println(EeAdrStr);// Запись byte массива
        EeAdrStr="";

        if(eeAddress > 32700){ //Если всё заполнилось то пойти писать по второму кругу
          eeAddress = 10; 
        }

        OneZjmyakButFirst=false; OneZjmyakButSecond=false; // Перезаряд
      }
      if( TimingButtFirst > TimingButtSecond ){      Serial.print("Proxod v obratnyu storonu:");     }//Serial.println("TimingButt1-TimingButt2)>0");Serial.println();

      OneZjmyakButFirst=false; OneZjmyakButSecond=false; // Перезаряд
      TimingButtFirst=0;       TimingButtSecond=0;       // Перезаряд
      WaitObrabotkaButt=millis(); // Присваиваим точку отсчёта переменной от которой будет отсчёт для активации буля возможности чтения кнопок
 //Обработка значений. Прибавка счётчика нажатий
}
 if (millis() - WaitObrabotkaButt > 300){ // Вместо 300 подставьте нужное вам значение паузы 
       CanReadBool=true;      
       WaitObrabotkaButt = millis(); //Serial.println ("10 seconds");
 }
}


void loop() {
  TmimgRefresh();// Обновляем время и заносим в нашу переменную
  ObrabotkaOneSide(1,Line1_PIN1,Line1_PIN2,Line1_countToday,L1CanReadBool  ,L1TimingButt1,L1TimingButt2,  L1OneZjmyakBut1,L1OneZjmyakBut2 ,L1WaitObrabotkaButt, L1DataStr); // захват прохода в одну сторону. Уведичение счётчика переданной линии
  ObrabotkaOneSide(2,Line2_PIN1,Line2_PIN2,Line2_countToday,L2CanReadBool  ,L2TimingButt1,L2TimingButt2,  L2OneZjmyakBut1,L2OneZjmyakBut2 ,L2WaitObrabotkaButt, L2DataStr); // захват прохода в одну сторону. Уведичение счётчика переданной линии
  Bluetooth(); // Принимает при подключении s, перезагружает и готов к работе // BT
   //PrintDebug();
}



unsigned long timingRefresh; // Переменная для хранения точки отсчета
void TmimgRefresh(){
if (millis() - timingRefresh > 1000){// Обновляем время // Вместо 10000 подставьте нужное вам значение паузы 
   RtcDateTime now = Rtc.GetDateTime(); // Обновляем время
   printDateTime(now); // Передаём изменённое время в функцию откуда извлекаем его сами
   timingRefresh = millis(); 
}

}

void PrintDebug(){
  static unsigned long timingPrint ;
  if (millis() - timingPrint > 3000){ // Вместо 10000 подставьте нужное вам значение паузы 
  Serial.println();
  Serial.print("L1TimingButt1:");Serial.print(L1TimingButt1);  Serial.print(" L1TimingButt2:");Serial.print(L1TimingButt2); Serial.print(" L1OneZjmyakBut1:");Serial.print(L1OneZjmyakBut1); Serial.print(" L1OneZjmyakBut2:");Serial.println(L1OneZjmyakBut2);
  Serial.print("L2TimingButt1:");Serial.print(L2TimingButt1);  Serial.print(" L2TimingButt2:");Serial.print(L2TimingButt2); Serial.print(" L2OneZjmyakBut1:");Serial.print(L2OneZjmyakBut1); Serial.print(" L2OneZjmyakBut2:");Serial.println(L2OneZjmyakBut2);
  Serial.println();
  timingPrint = millis(); 
  }
 
}

/*
        char dataFileName[sizeof(MyDateTimeStr)];
        MyDateTimeStr.toCharArray(dataFileName, sizeof(dataFileName));
        MyObject customVar = {
         NameLine,
         Line_countToday,
         dataFileName
  };
    EEPROM.put(eeAddress, customVar);
    */

  void Bluetooth(){
  // BT
  static bool IsEnterLine = false; // Упомянуты ли линии в сообщении
  static bool IsEnterDay = false; // Упомянуты ли дни в сообщении
  static bool Endline = false; // Говорит нам о том что принятая строка закончилась
  if (Serial.available() > 0) {
    //Serial.println("*");
    char inChar = (char)Serial.read();
    inputString += inChar;

    if (inChar == 'l') { //Проверка введённой линии (введена ли)
      IsEnterLine = 1;
      posL = inputString.indexOf('l'); //Узнаём индекс буквы l для парсинга данных
      Serial.print("IsEnterLine:"); Serial.print(IsEnterLine); Serial.print("posL:"); Serial.print(posL); Serial.println();

    }
    if (inChar == 'd') { //Проверка введённого кол-ва дней (введены ли дни)
      IsEnterDay = 1;
      posD = inputString.indexOf('d'); //Узнаём индекс буквы d для парсинга данных
      // Serial.print("IsEnterDay:");Serial.print(IsEnterDay); Serial.print(" posD:");Serial.print(posD);Serial.println();
    }
    if (inChar == '\n') { //При встреченном символе перевода строки
      //Serial.print("inputString:");Serial.println(inputString);
      Endline = true; // Пометили что наступил конец строки
      //inputString="";
    }
     if (inChar == 's') { //При встреченном символе перевода строки
     Serial.println("Reset");
     digitalWrite(resetPin,LOW);
    }
     if (inChar == 'a') { //Читать всё
     Serial.println("Печать всех данных:");
      // Прочитать просто всё
      static int old_eeAddress = eeAddress; // Присваиваем переменной old_eeAddress а чтоб не сбить ползунок а затем вернём всё назад
      eeAddress=10; //Устанавливаем ползунок в начале адресов для чтения
      Serial.println ();
      for(int i=0;i<15;i++){
        byte ReadLine = readEEPROM (rom, eeAddress);  Serial.print (ReadLine, DEC);  Serial.print (" ");    eeAddress+=1;   // display to confirm
       
        byte ReadDay = readEEPROM (rom, eeAddress);   Serial.print (ReadDay, DEC);   Serial.print (".");    eeAddress+=1;       
        byte ReadMonth = readEEPROM (rom, eeAddress); Serial.print (ReadMonth, DEC); Serial.print (".");    eeAddress+=1;
        byte ReadYear = readEEPROM (rom, eeAddress);  Serial.print (ReadYear, DEC);  Serial.print (" ");    eeAddress+=1;
            
        byte ReadHour = readEEPROM (rom, eeAddress);  Serial.print (ReadHour, DEC);  Serial.print (":");    eeAddress+=1;     
        byte ReadMin = readEEPROM (rom, eeAddress);   Serial.print (ReadMin, DEC);   Serial.print (":");    eeAddress+=1;    
        byte ReadSec = readEEPROM (rom, eeAddress);   Serial.println (ReadSec, DEC);                        eeAddress+=1;

 }
  eeAddress=old_eeAddress;
// Прочитать просто всё
    }
    // Тут мы разбираем входящие цифры линии и дней
    if (IsEnterLine == 1 && IsEnterDay == 1 && Endline == true) { //Если упомянуты линии дни и строка уже полностью у нас
      Serial.print("inputString:"); Serial.println(inputString);
      EnteredLine = inputString.substring(posL + 1, posD).toInt();
      EnteredDays = inputString.substring(posD + 1, inputString.length() ).toInt();

      Serial.print("EnteredLine:"); Serial.print(EnteredLine);     Serial.print(" EnteredDays:"); Serial.println(EnteredDays);
      Serial3.print("Я читаю из памяти линию: "); Serial3.print(EnteredLine);  Serial3.print(" Лог за: "); Serial3.print(EnteredDays); Serial3.println("дней");
      ReadLineDays( EnteredLine,EnteredDays );
      Endline = false; // Стока уже не полная мы обнуляем её
      inputString = ""; // Обнуление строки
      IsEnterLine = 0;   IsEnterDay = 0;
    }
    // Тут мы разбираем входящие цифры линии и дней
  }
  // BT
  }

void ReadLineDays(const byte& Line,const byte& Days){
 // if(Line == 1){    Serial.println("It is line 1!");  }
 // Принятие дней и перевод в дату от которой до которой вывести инфу
 byte TodayDay=byte(MyDateTimeStr.substring(3,5).toInt() );
 byte TodayMonth=byte( MyDateTimeStr.substring(0,2).toInt()  );
 byte TodayYear= byte( MyDateTimeStr.substring(8,10).toInt() ); 

 

 if(Days<=TodayDay){ //Если введённые дни меньше дня сегодняшнего. Вывод по введённой линии и кол-ву дней
     Serial.print("Будет выведена линия:");Serial.print( Line );  Serial.print(" Принято кол-во дней:");Serial.println(Days); 
     Serial.print("Будут выведены данные от ");     
     Serial.print(TodayDay-Days); Serial.print(".");  Serial.print(TodayMonth); Serial.print(".");   Serial.print(TodayYear); 
     Serial.print(" До ");
     Serial.print(TodayDay); Serial.print(".");       Serial.print(TodayMonth); Serial.print(".");   Serial.println(TodayYear); 

     // Cдесь сортировка будет по введённой линии и дням показ
     static int old_eeAddress = eeAddress; // Присваиваем переменной old_eeAddress а чтоб не сбить ползунок а затем вернём всё назад
     eeAddress=10; //Устанавливаем ползунок в начале адресов для чтения
     uint16_t countPodchet=0; // Временная переменная чтобы обьявить сколько же раз за заданный период считалась метка
     for(int i=0;i<15;i++){
         //Serial.print("=== Начало цикла Адрес контроль в цикле: ==="); Serial.println(eeAddress);
         //Проверяем соответствует ли считанная строка нашим параметрам
         bool GoNext=false; // Разрешает или запрещает проход к секции вывода 
         byte ReadLine = readEEPROM (rom, eeAddress);  eeAddress+=1; //Считываем линию
         if(ReadLine == Line ) //Проверяем соответствие считанной линии тому что мы попросили показать по блютуз.Если да то проверяем дальше
         {
             //Serial.print("Проверка считанной линии:"); Serial.println(ReadLine);
              byte ReadDay   = readEEPROM (rom, eeAddress); eeAddress+=1;                  //Считываем считанный из eeprom день
              byte ReadMonth = readEEPROM (rom, eeAddress);  eeAddress+=1;                 //Считываем считанный из eeprom месяц
              byte ReadYear  = readEEPROM (rom, eeAddress);                                //Считываем считанный из eeprom год
              //Serial.println();
              //Serial.print("ReadDay:"); Serial.print(ReadDay);              Serial.print(" TodayDay:"); Serial.println(TodayDay);
              //Serial.print("ReadMonth:"); Serial.print(ReadMonth);          Serial.print(" TodayMonth:"); Serial.println(TodayMonth);
              //Serial.print("ReadYear:"); Serial.print(ReadYear);            Serial.print(" TodayYear:"); Serial.println(TodayYear);
       
              if(ReadYear == TodayYear && ReadMonth == TodayMonth && ReadDay <= TodayDay && ReadDay >= (TodayDay-Days) ){ //Если считанный год и месяц совпали с текущим и считанный день меньше или равен текущему и считанный день больше текущий день - минус заданный из BT день
              GoNext=true; // Разрешить проход
              //Serial.print("GoNext= true");    Serial.print(" eeAddress:"); Serial.println(eeAddress);
              eeAddress-=3;countPodchet++;// Serial.println("countPodchet++"); 
              }
              else{  eeAddress+=4; GoNext=false; 
              //Serial.print("Выходим из else с ползунком:"); Serial.println(eeAddress);
              }
      }
      else{ eeAddress-=1;eeAddress+=7;} //Если линия не та что мы хотели вывести то откатить считанный адрес. И перепрыгнуть на следущую ячейку данных
      //Проверяем соответствует ли считанная строка нашим параметрам. Если да то GoNext cтановится true
      if(GoNext == true){
         //Serial.print("GoNext eeAddress:"); Serial.println(eeAddress);Serial.print("");
          Serial.print (ReadLine, DEC);  Serial.print (" "); eeAddress+=1; // display to confirm
      
          byte ReadDay = readEEPROM (rom, eeAddress);   Serial.print (ReadDay, DEC);    Serial.print (".");   eeAddress+=1;  
          byte ReadMonth = readEEPROM (rom, eeAddress); Serial.print (ReadMonth, DEC);  Serial.print (".");   eeAddress+=1;
          byte ReadYear = readEEPROM (rom, eeAddress);  Serial.print (ReadYear, DEC);   Serial.print (" ");   eeAddress+=1;
  
          byte ReadHour = readEEPROM (rom, eeAddress);  Serial.print (ReadHour, DEC);  Serial.print (":");    eeAddress+=1;
          byte ReadMin = readEEPROM (rom, eeAddress);   Serial.print (ReadMin, DEC);   Serial.print (":");    eeAddress+=1; 
          byte ReadSec = readEEPROM (rom, eeAddress);   Serial.println (ReadSec, DEC);                        eeAddress+=1;
      }
     //Serial.print("=== Конец цикла Адрес контроль в цикле: ==="); Serial.println(eeAddress);
 }
  Serial.print("Кол-во найденных проходов:"); Serial.println(countPodchet); 
  eeAddress=old_eeAddress;
// Cдесь сортировка будет по введённой линии и дням показ

 }   //Если введённые дни меньше дня сегодняшнего. Вывод по введённой линии и кол-ву дней
 else if(Days>TodayDay && Days<=30){  //Если введённые дни с BT больше сегодняшнего дня но меньше или равно 30. И это не конец года ( надо обработать )
     Serial.print("Будет выведена линия:");Serial.print( Line );  Serial.print(" Принято кол-во дней:");Serial.println(Days);
     int DayOt = TodayDay-Days; //DayOt =-7 //Сколько дней захватить надо в прошлом месяце [считаем по модулю]
     Serial.print("TodayDay");Serial.print(TodayDay);     Serial.print(" Days");Serial.print(Days);      Serial.print(" DayOt");Serial.println(DayOt); 

     int8_t ZaxvatDayLastMonth; //Сколько дней надо захватить в прошлом месяце
     ZaxvatDayLastMonth=MonthArr[TodayMonth-1]+ DayOt; // Узнали с какого дня прошлого месяца будет начинать выводится информация
     
     if(TodayMonth != 1){ // Если сейчас не первый месяц года (прикол с переходом через год - надо уменьшить год)
        Serial.print("Будут выведены данные от "); Serial.print(ZaxvatDayLastMonth); Serial.print(".");  Serial.print(TodayMonth-1); Serial.print("."); Serial.print(TodayYear); 
        Serial.print(" До "); Serial.print(TodayDay); Serial.print("."); Serial.print(TodayMonth); Serial.print("."); Serial.println(TodayYear); 
     }
     else{ // в строке отсчёт от - уменьшить год на 1цу
        Serial.print("Будут выведены данные от "); Serial.print(ZaxvatDayLastMonth); Serial.print(".");  Serial.print(TodayMonth-1); Serial.print("."); Serial.print(TodayYear-1); 
        Serial.print(" До "); Serial.print(TodayDay); Serial.print("."); Serial.print(TodayMonth); Serial.print("."); Serial.println(TodayYear); 
     }

    //Cюда вставляем вывод
      
    //Cюда вставляем вывод
 }
 else {Serial.println("Не больше 30ти дней! Введи 30 или меньше");}
}                 

















































































 

  byte writeEEPROM (byte device, unsigned int addr, byte * data, byte len )
{
  byte err;
  byte counter;

  if (len > BUFFER_LENGTH)  // 32 (in Wire.h)
    return 0xFF;  // too long

  Wire.beginTransmission(device);
  Wire.write ((byte) (addr >> 8));    // high order byte
  Wire.write ((byte) (addr & 0xFF));  // low-order byte
  Wire.write (data, len);
  err = Wire.endTransmission ();

  if (err != 0)
    return err;  // cannot write to device

  // wait for write to finish by sending address again
  //  ... give up after 100 attempts (1/10 of a second)
  for (counter = 0; counter < 100; counter++)
  {
    delayMicroseconds (300);  // give it a moment
    Wire.beginTransmission (device);
    Wire.write ((byte) (addr >> 8));    // high order byte
    Wire.write ((byte) (addr & 0xFF));  // low-order byte
    err = Wire.endTransmission ();
    if (err == 0)
      break;
  }

  return err;

} // end of writeEEPROM

// write one byte to device, returns non-zero on error
byte writeEEPROM (byte device, unsigned int addr, byte data )
{
  return writeEEPROM (device, addr, &data, 1);
} // end of writeEEPROM

// read len (max 32) bytes from device, returns non-zero on error
//  return code: 0xFF means buffer too long
//               0xFE means device did not return all requested bytes
//             other: other error (eg. device not present)

// Note that if reading multiple bytes the address plus
//  length must not cross a 64-byte boundary or it will "wrap"

byte readEEPROM (byte device, unsigned int addr, byte * data, byte len )
{
  byte err;
  byte counter;

  if (len > BUFFER_LENGTH)  // 32 (in Wire.h)
    return 0xFF;  // too long

  Wire.beginTransmission (device);
  Wire.write ((byte) (addr >> 8));    // high order byte
  Wire.write ((byte) (addr & 0xFF));  // low-order byte
  err = Wire.endTransmission ();

  if (err != 0)
    return err;  // cannot read from device

  // initiate blocking read into internal buffer
  Wire.requestFrom (device, len);

  // pull data out of Wire buffer into our buffer
  for (counter = 0; counter < len; counter++)
  {
    data [counter] = Wire.read ();
  }

  return 0;  // OK
}  // end of readEEPROM

// read one byte from device, returns 0xFF on error
byte readEEPROM (byte device, unsigned int addr )
{
  byte temp;

  if (readEEPROM (device, addr, &temp, 1) == 0)
    return temp;

  return 0xFF;

}  // end of readEEPROM

  //ExtEEPROM
  // Первое чтение (без него похоже не пишет) 32700/30 = 1090 и минус 100 так как пишем с 100го адреса
  //char message[27]; //buffer
  //for (int i = 0; i < 990; i++) {
  //  eeprom.read(eeAddress, (byte *) message, sizeof(message));
  //  Serial.println(message);
  //  eeAddress += 30; // Сдвиг адреса
  //}
  // Первое чтение (без него похоже не пишет) 32700/30 = 1090 и минус 100 так как пишем с 100го адреса
  //eeAddress = 100;    Serial.println();
  //ExtEEPROM
/*
    // В этом месте в терминал выведем распечатку лога всех линий а затем нужно линии
  static int old_eeAddress = eeAddress; // Присваиваем переменной old_eeAddress а чтоб не сбить ползунок а затем вернём всё назад
  eeAddress=10;

  for(int i=0;i<15;i++){
  byte ReadLine = readEEPROM (rom, eeAddress); Serial.print (ReadLine, DEC);  Serial.print (" ");  // display to confirm
  eeAddress+=1;
  
  int ReadLineCount = readEEPROM (rom, eeAddress);Serial.print (ReadLineCount, DEC);  Serial.print (" "); // display to confirm
  eeAddress+=1;
  
  byte ReadMonth = readEEPROM (rom, eeAddress); Serial.print (ReadMonth, DEC);   Serial.print (".");
  eeAddress+=1;

  byte ReadDay = readEEPROM (rom, eeAddress); Serial.print (ReadDay, DEC);  Serial.print ("."); 
  eeAddress+=1;

  int ReadYear = readEEPROM (rom, eeAddress);  Serial.print (ReadYear, DEC);   Serial.print (" ");
  eeAddress+=1;

  byte ReadHour = readEEPROM (rom, eeAddress);  Serial.print (ReadHour, DEC);  Serial.print (":"); 
  eeAddress+=1;

  byte ReadMin = readEEPROM (rom, eeAddress);  Serial.print (ReadMin, DEC);   Serial.print (":"); 
  eeAddress+=1;

  byte ReadSec = readEEPROM (rom, eeAddress);   Serial.println (ReadSec, DEC); 
  eeAddress+=1;
  }
  eeAddress=old_eeAddress;
    // В этом месте в терминал выведем распечатку лога всех линий а затем нужно линии
    */