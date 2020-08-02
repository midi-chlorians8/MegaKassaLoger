#include <Arduino.h>
#include <Definition.h>

//EEPROM
#include <Wire.h>
const byte rom = 0x50; // Address of 24LC256 eeprom chip
int eeAddress;
String EeAdrStr = "";
char EeAdrStrBuf[6];                    // Промежуточный контейнер для значения ползунка по адресам перед передачей в массив байт
byte MyArrayData[6];                    // Контейнер в который перейдёт массив сhar
byte ReadPolzunArr[sizeof MyArrayData]; // Массив для чтения ползун значения

#define AllMemoryExtEE1_7Yach 4671
//                       1   2   3   4   5   6   7   8   9  10  11  12
int8_t MonthArr[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//EEPROM

#define SendBT_Tubler
#define Debug_Tubler

void setup()
{

  // BT
  digitalWrite(resetPin, HIGH);
  delay(200);

  pinMode(resetPin, OUTPUT); // инициализируем цифровой пин в качестве выхода
  Serial3.begin(115200);
  delay(200);
  Serial3.println(teststring);

  //inputString.reserve(200);
  // BT
  Serial.begin(115200);
  delay(200); //while(!Serial){}

  Serial.print("MonthArr[2]");Serial.println(MonthArr[2]);

  //Кнопки и счётчики срабатываний
  PinMode(); //Высталяем пины кнопок на вход
  Serial.println();
  Serial.println(); //Serial.println();  //Serial.print(F("TimingButt1:"));Serial.print(L1TimingButt1);  Serial.print(F(" TimingButt2:"));Serial.println(L1TimingButt2);
  //Кнопки и счётчики срабатываний

  // RTC
  Serial.print(F("compiled: "));
  Serial.print(__DATE__);
  Serial.println(__TIME__);
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

      // Rtc.SetDateTime(compiled);
    }
  }
  // RTC

  //ExtEEPROM2
  byte err;
#ifdef SendBT_Tubler
  Serial3.print(F("I read. "));
#else
  Serial.print(F("I read. "));
#endif
  // Первый прочитался
  err = readEEPROM(rom, 1, ReadPolzunArr, sizeof(ReadPolzunArr));
  //Serial.print("Polzunok is:"); Serial.println ((char *) ReadPolzunArr);  // display to confirm
  EeAdrStr = (char *)ReadPolzunArr;
  Serial.print(F("EeAdrStr(Polzunok) is:"));
  Serial.print(EeAdrStr);
  Serial.print(F(" Текущее время: "));
  Serial.println(MyDateTimeStr);
  eeAddress = EeAdrStr.toInt();
  //ExtEEPROM2
}

void ObrabotkaOneSide(const byte NameLine, int8_t pin, int8_t pin2, bool &CanReadBool, unsigned long &TimingButtFirst, unsigned long &TimingButtSecond, bool &OneZjmyakButFirst, bool &OneZjmyakButSecond, unsigned long &WaitObrabotkaButt)
{ //Функция должна при нажатии последовательно кнопки 1, а затем кнопки 2 увеличить глобальный счётчик прохода в линии

  //static bool CanReadBool = true;

  //Ввод значений нажатия кнопки. Результат нажатия були OneZjmyakBut1 и OneZjmyakBut2
  if (CanReadBool == true)
  { //Если разрешено читать кнопки
    if (digitalRead(pin) == 0)
    { // Если нажата кнопка 1
      if (OneZjmyakButFirst == false)
      {
        TimingButtFirst = millis(); // Присвоить значение таймера в переменную
        //Serial.print("[pin]TimingButt1:");Serial.print("");Serial.print(" TimingButt2:");Serial.println();
        OneZjmyakButFirst = true;
      }
    }
    if (digitalRead(pin2) == 0)
    { // Если нажата кнопка 2
      if (OneZjmyakButSecond == false)
      {
        TimingButtSecond = millis(); // Присвоить значение таймера в переменную
        //Serial.print("[pin2]TimingButt1:");Serial.print("");Serial.print(" TimingButt2:");Serial.println();
        OneZjmyakButSecond = true;
      }
    }
  } //Если разрешено читать кнопки
    //Ввод значений нажатия кнопки. Результат нажатия були OneZjmyakBut1 и OneZjmyakBut2

  //Обработка значений. Прибавка счётчика нажатий
  if (OneZjmyakButFirst == true && OneZjmyakButSecond == true)
  {
    digitalWrite(13,HIGH);
    CanReadBool = false; // Запретить чтение кнопок
                         //if( (TimingButt1-TimingButt2)<0  ){
    if (TimingButtFirst < TimingButtSecond)
    {
      if (eeAddress > 32700)
      {
        eeAddress = 10;
      } //Если всё заполнилось то пойти писать по второму кругу

      //Line_countToday++; //Serial.print(F("Proxod Dobavlen:")); Serial.print(F("TB1-TB2)<0 "));       Serial.print(NameLine); Serial.print(F("Line_countToday:"));        Serial.print(Line_countToday); Serial.print(" ");        Serial.print(MyDateTimeStr); Serial.println();
      // DataStr=String(NameLine) + " " + MyDateTimeStr  + " " + Line_countToday;  Serial.print("DataStr:");Serial.println(DataStr);

      // Формирование и запись последовательности данных в EEPROM
      byte Line = NameLine;
      writeEEPROM(rom, eeAddress, Line);
      eeAddress += 1;

      byte Day = byte(MyDateTimeStr.substring(3, 5).toInt());
      writeEEPROM(rom, eeAddress, Day);
      eeAddress += 1;
      byte Month = byte(MyDateTimeStr.substring(0, 2).toInt());
      writeEEPROM(rom, eeAddress, Month);
      eeAddress += 1;
      byte Year = byte(MyDateTimeStr.substring(8, 10).toInt());
      writeEEPROM(rom, eeAddress, Year);
      eeAddress += 1;

      byte Hour = byte(MyDateTimeStr.substring(11, 13).toInt());
      writeEEPROM(rom, eeAddress, Hour);
      eeAddress += 1;
      byte Min = byte(MyDateTimeStr.substring(14, 16).toInt());
      writeEEPROM(rom, eeAddress, Min);
      eeAddress += 1;
      byte Sec = byte(MyDateTimeStr.substring(17, 19).toInt());
      writeEEPROM(rom, eeAddress, Sec);
      eeAddress += 1;
#ifdef Debug_Tubler
      Serial.print("MyLine:");
      Serial.print(Line);
      Serial.print("\tMyDay:");
      Serial.print(Day);
      Serial.print(" MyMonth:");
      Serial.print(Month);
      Serial.print(" MyYear:");
      Serial.print(Year);
      Serial.print("\tMyHour:");
      Serial.print(Hour);
      Serial.print(" MyMin:");
      Serial.print(Min);
      Serial.print(" MySec:");
      Serial.println(Sec);
      Serial.println();
#endif
      // И далее записываем в eeprom ячейку 1 значение ползунка в конце записи
      EeAdrStr = String(eeAddress);
      char EeAdrStrBuf[6];
      EeAdrStr.toCharArray(EeAdrStrBuf, 6);
      for (uint8_t i = 0; i < sizeof(MyArrayData); i++)
      {
        MyArrayData[i] = byte(EeAdrStrBuf[i]);
      } //Преобразование массива сhar в массив byte

      writeEEPROM(rom, 1, MyArrayData, sizeof(MyArrayData));
#ifdef Debug_Tubler
      Serial.print("I write to eeprom Polzunok val:");
      Serial.println(EeAdrStr); // Запись byte массива
#endif
      EeAdrStr = "";

      OneZjmyakButFirst = false;
      OneZjmyakButSecond = false; // Перезаряд
      digitalWrite(13,LOW);
    }
    if (TimingButtFirst > TimingButtSecond)
    {
#ifdef Debug_Tubler
      Serial.println("Proxod v obratnyu storonu:");
#endif
    }
    OneZjmyakButFirst = false;
    OneZjmyakButSecond = false; // Перезаряд
    TimingButtFirst = 0;
    TimingButtSecond = 0;         // Перезаряд
    WaitObrabotkaButt = millis(); // Присваиваим точку отсчёта переменной от которой будет отсчёт для активации буля возможности чтения кнопок
                                  //Обработка значений. Прибавка счётчика нажатий
  }
  if (millis() - WaitObrabotkaButt > 250)
  { // Вместо 300 подставьте нужное вам значение паузы
    CanReadBool = true;
    WaitObrabotkaButt = millis(); //Serial.println ("10 seconds");
  }
}

void loop()
{
  while (1)
  {                 //Ускорение на 1мкс
    TmimgRefresh(); // Обновляем время и заносим в нашу переменную

    ObrabotkaOneSide(1, Line1_PIN1, Line1_PIN2, L1CanReadBool, L1TimingButt1, L1TimingButt2, L1OneZjmyakBut1, L1OneZjmyakBut2, L1WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(2, Line2_PIN1, Line2_PIN2, L2CanReadBool, L2TimingButt1, L2TimingButt2, L2OneZjmyakBut1, L2OneZjmyakBut2, L2WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(3, Line3_PIN1, Line3_PIN2, L3CanReadBool, L3TimingButt1, L3TimingButt2, L3OneZjmyakBut1, L3OneZjmyakBut2, L3WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(4, Line4_PIN1, Line4_PIN2, L4CanReadBool, L4TimingButt1, L4TimingButt2, L4OneZjmyakBut1, L4OneZjmyakBut2, L4WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(5, Line5_PIN1, Line5_PIN2, L5CanReadBool, L5TimingButt1, L5TimingButt2, L5OneZjmyakBut1, L5OneZjmyakBut2, L5WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(6, Line6_PIN1, Line6_PIN2, L6CanReadBool, L6TimingButt1, L6TimingButt2, L6OneZjmyakBut1, L6OneZjmyakBut2, L6WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(7, Line7_PIN1, Line7_PIN2, L7CanReadBool, L7TimingButt1, L7TimingButt2, L7OneZjmyakBut1, L7OneZjmyakBut2, L7WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(8, Line8_PIN1, Line8_PIN2, L8CanReadBool, L8TimingButt1, L8TimingButt2, L8OneZjmyakBut1, L8OneZjmyakBut2, L8WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(9, Line9_PIN1, Line9_PIN2, L9CanReadBool, L9TimingButt1, L9TimingButt2, L9OneZjmyakBut1, L9OneZjmyakBut2, L9WaitObrabotkaButt);          // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(10, Line10_PIN1, Line10_PIN2, L10CanReadBool, L10TimingButt1, L10TimingButt2, L10OneZjmyakBut1, L10OneZjmyakBut2, L10WaitObrabotkaButt); // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(11, Line11_PIN1, Line11_PIN2, L11CanReadBool, L11TimingButt1, L11TimingButt2, L11OneZjmyakBut1, L11OneZjmyakBut2, L11WaitObrabotkaButt); // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(12, Line12_PIN1, Line12_PIN2, L12CanReadBool, L12TimingButt1, L12TimingButt2, L12OneZjmyakBut1, L12OneZjmyakBut2, L12WaitObrabotkaButt); // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(13, Line13_PIN1, Line13_PIN2, L13CanReadBool, L13TimingButt1, L13TimingButt2, L13OneZjmyakBut1, L13OneZjmyakBut2, L13WaitObrabotkaButt); // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(14, Line14_PIN1, Line14_PIN2, L14CanReadBool, L14TimingButt1, L14TimingButt2, L14OneZjmyakBut1, L14OneZjmyakBut2, L14WaitObrabotkaButt); // захват прохода в одну сторону. Уведичение счётчика переданной линии
    ObrabotkaOneSide(15, Line15_PIN1, Line15_PIN2, L15CanReadBool, L15TimingButt1, L15TimingButt2, L15OneZjmyakBut1, L15OneZjmyakBut2, L15WaitObrabotkaButt); // захват прохода в одну сторону. Уведичение счётчика переданной линии

    Bluetooth(); // Принимает при подключении s, перезагружает и готов к работе // BT

    //PrintDebug();
  } //Ускорение на 1мкс
}

unsigned long timingRefresh; // Переменная для хранения точки отсчета
void TmimgRefresh()
{
  if (millis() - timingRefresh > 1000)
  {                                      // Обновляем время // Вместо 10000 подставьте нужное вам значение паузы
    RtcDateTime now = Rtc.GetDateTime(); // Обновляем время
    printDateTime(now);                  // Передаём изменённое время в функцию откуда извлекаем его сами
    timingRefresh = millis();
  }
}

void PrintDebug()
{
  static unsigned long timingPrint;
  if (millis() - timingPrint > 3000)
  { // Вместо 10000 подставьте нужное вам значение паузы
    Serial.println();
    Serial.print(F("L1TimingButt1:"));
    Serial.print(L1TimingButt1);
    Serial.print(F(" L1TimingButt2:"));
    Serial.print(L1TimingButt2);
    Serial.print(F(" L1OneZjmyakBut1:"));
    Serial.print(L1OneZjmyakBut1);
    Serial.print(" L1OneZjmyakBut2:");
    Serial.println(L1OneZjmyakBut2);
    Serial.print(F("L2TimingButt1:"));
    Serial.print(L2TimingButt1);
    Serial.print(F(" L2TimingButt2:"));
    Serial.print(L2TimingButt2);
    Serial.print(F(" L2OneZjmyakBut1:"));
    Serial.print(L2OneZjmyakBut1);
    Serial.print(" L2OneZjmyakBut2:");
    Serial.println(L2OneZjmyakBut2);
    Serial.println();
    timingPrint = millis();
  }
}

void Bluetooth()
{
  // BT
  static bool IsEnterLine = false; // Упомянуты ли линии в сообщении
  static bool IsEnterDay = false;  // Упомянуты ли дни в сообщении
  static bool Endline = false;     // Говорит нам о том что принятая строка закончилась
#ifdef SendBT_Tubler
  if (Serial3.available() > 0)
  {
    Serial.println("Serial3");
    char inChar = (char)Serial3.read();
#else
  while (Serial.available() > 0)
  {
    char inChar = (char)Serial.read();
#endif
    inputString += inChar;

    if (inChar == 'l')
    { //Проверка введённой линии (введена ли)
      IsEnterLine = 1;
      posL = inputString.indexOf('l'); //Узнаём индекс буквы l для парсинга данных
      //Serial.print(F("IsEnterLine:")); Serial.print(IsEnterLine); Serial.print(F("posL:")); Serial.print(posL); Serial.println();
    }
    if (inChar == 'd')
    { //Проверка введённого кол-ва дней (введены ли дни)
      IsEnterDay = 1;
      posD = inputString.indexOf('d'); //Узнаём индекс буквы d для парсинга данных
      // Serial.print("IsEnterDay:");Serial.print(IsEnterDay); Serial.print(" posD:");Serial.print(posD);Serial.println();
    }
    if (inChar == 'e')
    { //Удалить всё

      eeAddress = 10; //Устанавливаем ползунок в начале адресов для чтения

      for (int i = 1; i <= AllMemoryExtEE1_7Yach; i++)
      {
        writeEEPROM(rom, eeAddress, 0);
        eeAddress += 1;

        byte Day = byte(MyDateTimeStr.substring(3, 5).toInt());
        writeEEPROM(rom, eeAddress, 0);
        eeAddress += 1;
        byte Month = byte(MyDateTimeStr.substring(0, 2).toInt());
        writeEEPROM(rom, eeAddress, 0);
        eeAddress += 1;
        byte Year = byte(MyDateTimeStr.substring(8, 10).toInt());
        writeEEPROM(rom, eeAddress, 0);
        eeAddress += 1;

        byte Hour = byte(MyDateTimeStr.substring(11, 13).toInt());
        writeEEPROM(rom, eeAddress, 0);
        eeAddress += 1;
        byte Min = byte(MyDateTimeStr.substring(14, 16).toInt());
        writeEEPROM(rom, eeAddress, 0);
        eeAddress += 1;
        byte Sec = byte(MyDateTimeStr.substring(17, 19).toInt());
        writeEEPROM(rom, eeAddress, 0);
        eeAddress += 1;
#ifdef SendBT_Tubler
        Serial3.println(eeAddress);
#else
        Serial.println(eeAddress);
#endif
      }
      eeAddress = 10;
      // И записать в EEPROM что ползунок должен с addr 10ти начинать записывать
      String EeAdrStr = "10";
      EeAdrStr.toCharArray(EeAdrStrBuf, 6);
      byte MyArrayData[6]; //Обозначили размер byte коробки в которую вписываем сhar array
      // Первый пошёл
      for (int i = 0; i < sizeof(MyArrayData); i++)
      {
        MyArrayData[i] = byte(EeAdrStrBuf[i]);
      }                                                      //Преобразование массива сhar в массив byte
      writeEEPROM(rom, 1, MyArrayData, sizeof(MyArrayData)); // Запись byte массива

#ifdef SendBT_Tubler
      Serial3.println();
      Serial3.println(F("Всё стёрто"));
#else
      Serial.println();
      Serial.println(F("Всё стёрто"));
#endif
    }
    if (inChar == '\n')
    { //При встреченном символе перевода строки
      //Serial.print("inputString:");Serial.println(inputString);
      Endline = true; // Пометили что наступил конец строки
      //inputString="";
    }
    if (inChar == 's')
    { //При встреченном символе перевода строки
      Serial.println(F("Reset"));
      digitalWrite(resetPin, LOW);
    }
    if (inputString == "t\n")
    { //При встреченном символе перевода строки
#ifdef SendBT_Tubler
      Serial3.print(F("Текущее время: "));
      Serial3.print(MyDateTimeStr);
      Serial3.print(F(" Ползунок на адресе: "));
      Serial3.println(eeAddress);
#else
      Serial.print(F("Текущее время: "));
      Serial.print(MyDateTimeStr);
      Serial.print(F(" Ползунок на адресе: "));
      Serial.println(eeAddress);
#endif
      inputString = "";
    }
    if (inChar == 'a')
    { //Читать всё
#ifdef SendBT_Tubler
      Serial3.println();
      Serial3.println(F("Печать всех данных:"));
#else
      Serial.println();
      Serial.println(F("Печать всех данных:"));
#endif
      // Прочитать просто всё
      static int old_eeAddressFromCharA = eeAddress; // Присваиваем переменной old_eeAddress а чтоб не сбить ползунок а затем вернём всё назад
      eeAddress = 10;                                //Устанавливаем ползунок в начале адресов для чтения

      for (int i = 1; i <= AllMemoryExtEE1_7Yach; i++)
      {
        byte ReadLine = readEEPROM(rom, eeAddress);
        eeAddress += 1; // display to confirm
        byte ReadDay = readEEPROM(rom, eeAddress);
        eeAddress += 1;
        byte ReadMonth = readEEPROM(rom, eeAddress);
        eeAddress += 1;
        byte ReadYear = readEEPROM(rom, eeAddress);
        eeAddress += 1;

        byte ReadHour = readEEPROM(rom, eeAddress);
        eeAddress += 1;
        byte ReadMin = readEEPROM(rom, eeAddress);
        eeAddress += 1;
        byte ReadSec = readEEPROM(rom, eeAddress);
        eeAddress += 1;
#ifdef SendBT_Tubler
        Serial3.print("#");
        Serial3.print(i);
        Serial3.print(F("\t "));
        Serial3.print(ReadLine, DEC);
        Serial3.print(" ");
        Serial3.print(ReadDay, DEC);
        Serial3.print(".");
        Serial3.print(ReadMonth, DEC);
        Serial3.print(".");
        Serial3.print(ReadYear, DEC);
        Serial3.print(" ");
        if (ReadDay < 10)
        {
          Serial3.print(F("\t"));
        }
        Serial3.print("\t");
        Serial3.print(ReadHour, DEC);
        Serial3.print(":");
        Serial3.print(ReadMin, DEC);
        Serial3.print(":");
        Serial3.print(ReadSec, DEC);
        if (ReadSec < 10)
        {
          Serial3.print(F("\t"));
        }
        Serial3.print("\t addr: ");
        Serial3.println(eeAddress); // Убрать при выпуске в свет
#else
        Serial.print("#");
        Serial.print(i);
        Serial.print(F("\t "));
        Serial.print(ReadLine, DEC);
        Serial.print(" ");
        Serial.print(ReadDay, DEC);
        Serial.print(".");
        Serial.print(ReadMonth, DEC);
        Serial.print(".");
        Serial.print(ReadYear, DEC);
        Serial.print(" ");
        //if(ReadDay<10){Serial.print (F("\t")); }
        Serial.print("\t");
        Serial.print(ReadHour, DEC);
        Serial.print(":");
        Serial.print(ReadMin, DEC);
        Serial.print(":");
        Serial.print(ReadSec, DEC);
        if (ReadSec < 10)
        {
          Serial.print(F("\t"));
        }
        Serial.print("\t addr: ");
        Serial.println(eeAddress); // Убрать при выпуске в свет
#endif
      }
      eeAddress = old_eeAddressFromCharA;
      // Прочитать просто всё
#ifdef SendBT_Tubler
      Serial3.end();         // Странный костыль от глюков
      Serial3.begin(115200); // Странный костыль от глюков
#else
      Serial.end();                // Странный костыль от глюков
      Serial.begin(115200);        // Странный костыль от глюков
#endif
    }
    // Тут мы разбираем входящие цифры линии и дней
    if (IsEnterLine == 1 && IsEnterDay == 1 && Endline == true)
    { //Если упомянуты линии дни и строка уже полностью у нас
      Serial.print(F("inputString:"));
      Serial.println(inputString);
      EnteredLine = inputString.substring(posL + 1, posD).toInt();
      EnteredDays = inputString.substring(posD + 1, inputString.length()).toInt();

      Serial.print(F("EnteredLine:"));
      Serial.print(EnteredLine);
      Serial.print(F(" EnteredDays:"));
      Serial.println(EnteredDays);
      Serial3.print(F("Я читаю из памяти линию: "));
      Serial3.print(EnteredLine);
      Serial3.print(F(" Лог за: "));
      Serial3.print(EnteredDays);
      Serial3.println(F("дней"));
      ReadLineDays(EnteredLine, EnteredDays);
      Endline = false;  // Стока уже не полная мы обнуляем её
      inputString = ""; // Обнуление строки
      IsEnterLine = 0;
      IsEnterDay = 0;
    }
    // Тут мы разбираем входящие цифры линии и дней
    //inputString="";
  }
  // BT
}

void ReadLineDays(const byte &Line, const byte &Days)
{
  // if(Line == 1){    Serial.println("It is line 1!");  }
  // Принятие дней и перевод в дату от которой до которой вывести инфу
  byte TodayDay = byte(MyDateTimeStr.substring(3, 5).toInt());
  byte TodayMonth = byte(MyDateTimeStr.substring(0, 2).toInt());
  byte TodayYear = byte(MyDateTimeStr.substring(8, 10).toInt());
  //Serial.print("MonthArr[TodayMonth-1]");Serial.println(MonthArr[12]);
  if (Days <= TodayDay)
  { //Если введённые дни меньше дня сегодняшнего. Вывод по введённой линии и кол-ву дней
#ifdef SendBT_Tubler
    Serial3.print("Будет выведена линия:");
    Serial3.print(Line);
    Serial3.print(" Принято кол-во дней:");
    Serial3.println(Days);
    Serial3.print("Будут выведены данные от ");

    if ((TodayDay - Days) != 0)
    { //
      Serial3.print(TodayDay - Days);
      Serial3.print(".");
      Serial3.print(TodayMonth); // Печатаем месяц
    }
    else
    { //Случай если TodayDay-Days = 0.
      if (TodayMonth == 1)
      { //Если первый месяц в году
        Serial3.print(MonthArr[12]);
        Serial3.print(".");
        Serial3.print("12"); // Печатаем месяц
      }
      else
      { //Если НЕ первый месяц в году
        Serial3.print(MonthArr[TodayMonth - 1]);
        Serial3.print(".");
        Serial3.print(TodayMonth - 1); // Печатаем месяц
      }
    }
    Serial3.print(".");
    Serial3.print(TodayYear);

    Serial3.print(" До ");
    Serial3.print(TodayDay);
    Serial3.print(".");
    Serial3.print(TodayMonth);
    Serial3.print(".");
    Serial3.println(TodayYear);
#else
    Serial.print("Будет выведена линия:");
    Serial.print(Line);
    Serial.print(" Принято кол-во дней:");
    Serial.println(Days);
    Serial.print("Будут выведены данные от ");
    if ((TodayDay - Days) != 0)
    { //
      Serial.print(TodayDay - Days);
      Serial.print(".");
      Serial.print(TodayMonth); // Печатаем месяц
    }
    else
    { //Случай если TodayDay-Days = 0.
      if (TodayMonth == 1)
      { //Если первый месяц в году
        Serial.print(MonthArr[12]);
        Serial.print(".");
        Serial.print("12"); // Печатаем месяц
      }
      else
      { //Если НЕ первый месяц в году
        Serial.print(MonthArr[TodayMonth - 1]);
        Serial.print(".");
        Serial.print(TodayMonth - 1); // Печатаем месяц
      }
    }
    Serial.print(".");
    Serial.print(TodayYear);
    Serial.print(" До ");
    Serial.print(TodayDay);
    Serial.print(".");
    Serial.print(TodayMonth);
    Serial.print(".");
    Serial.println(TodayYear);
#endif

    // Cдесь сортировка будет по введённой линии и дням показ (Если дней введённых меньше чем даёт текущая дата)
    int old_eeAddress = eeAddress; // Присваиваем переменной old_eeAddress а чтоб не сбить ползунок а затем вернём всё назад
    eeAddress = 10;                //Устанавливаем ползунок в начале адресов для чтения
    uint16_t countPodchet = 0;     // Временная переменная чтобы обьявить сколько же раз за заданный период считалась метка
    for (int i = 1; i <= AllMemoryExtEE1_7Yach; i++)
    {
      //Serial.print("=== Начало цикла Адрес контроль в цикле: ==="); Serial.println(eeAddress);
      //Проверяем соответствует ли считанная строка нашим параметрам
      bool GoNext = false; // Разрешает или запрещает проход к секции вывода
      byte ReadLine = readEEPROM(rom, eeAddress);
      eeAddress += 1;       //Считываем линию
      if (ReadLine == Line) //Проверяем соответствие считанной линии тому что мы попросили показать по блютуз.Если да то проверяем дальше
      {
        //Serial.print("Проверка считанной линии:"); Serial.println(ReadLine);
        byte ReadDay = readEEPROM(rom, eeAddress);
        eeAddress += 1; //Считываем считанный из eeprom день
        byte ReadMonth = readEEPROM(rom, eeAddress);
        eeAddress += 1;                             //Считываем считанный из eeprom месяц
        byte ReadYear = readEEPROM(rom, eeAddress); //Считываем считанный из eeprom год
        //Serial.println();
        //Serial.print("ReadDay:"); Serial.print(ReadDay);              Serial.print(" TodayDay:"); Serial.println(TodayDay);
        //Serial.print("ReadMonth:"); Serial.print(ReadMonth);          Serial.print(" TodayMonth:"); Serial.println(TodayMonth);
        //Serial.print("ReadYear:"); Serial.print(ReadYear);            Serial.print(" TodayYear:"); Serial.println(TodayYear);

        if (ReadYear == TodayYear && ReadMonth == TodayMonth && ReadDay <= TodayDay && ReadDay >= (TodayDay - Days))
        {                //Если считанный год и месяц совпали с текущим и считанный день меньше или равен текущему и считанный день больше текущий день - минус заданный из BT день
          GoNext = true; // Разрешить проход
                         //Serial.print("GoNext= true");    Serial.print(" eeAddress:"); Serial.println(eeAddress);
          eeAddress -= 3;
          countPodchet++; // Serial.println("countPodchet++");
        }
        else
        {
          eeAddress += 4;
          GoNext = false;
          //Serial.print("Выходим из else с ползунком:"); Serial.println(eeAddress);
        }
      }
      else
      {
        eeAddress -= 1;
        eeAddress += 7;
      } //Если линия не та что мы хотели вывести то откатить считанный адрес. И перепрыгнуть на следущую ячейку данных
      //Проверяем соответствует ли считанная строка нашим параметрам. Если да то GoNext cтановится true
      if (GoNext == true)
      {
        //Serial.print("GoNext eeAddress:"); Serial.println(eeAddress);Serial.print("");
        eeAddress += 1; // display to confirm

        byte ReadDay = readEEPROM(rom, eeAddress);
        eeAddress += 1;
        byte ReadMonth = readEEPROM(rom, eeAddress);
        eeAddress += 1;
        byte ReadYear = readEEPROM(rom, eeAddress);
        eeAddress += 1;

        byte ReadHour = readEEPROM(rom, eeAddress);
        eeAddress += 1;
        byte ReadMin = readEEPROM(rom, eeAddress);
        eeAddress += 1;
        byte ReadSec = readEEPROM(rom, eeAddress);
        eeAddress += 1;
#ifdef SendBT_Tubler
        Serial3.print("#");
        Serial3.print(i);
        Serial3.print(" ");
        Serial3.print(ReadLine, DEC);
        Serial3.print(" ");
        Serial3.print(ReadDay, DEC);
        Serial3.print(".");
        Serial3.print(ReadMonth, DEC);
        Serial3.print(".");
        Serial3.print(ReadYear, DEC);
        Serial3.print(" ");
        Serial3.print(ReadHour, DEC);
        Serial3.print(":");
        Serial3.print(ReadMin, DEC);
        Serial3.print(":");
        Serial3.println(ReadSec, DEC);
#else
        Serial.print("#");
        Serial.print(i);
        Serial.print(" ");
        Serial.print(ReadLine, DEC);
        Serial.print(" ");
        Serial.print(ReadDay, DEC);
        Serial.print(".");
        Serial.print(ReadMonth, DEC);
        Serial.print(".");
        Serial.print(ReadYear, DEC);
        Serial.print(" ");
        Serial.print(ReadHour, DEC);
        Serial.print(":");
        Serial.print(ReadMin, DEC);
        Serial.print(":");
        Serial.println(ReadSec, DEC);
#endif
      }
      //Serial.print("=== Конец цикла Адрес контроль в цикле: ==="); Serial.println(eeAddress);
    }
#ifdef SendBT_Tubler
    Serial3.print("Кол-во найденных проходов:");
    Serial3.println(countPodchet);
#else
    Serial.print("Кол-во найденных проходов:");
    Serial.println(countPodchet);
#endif
    eeAddress = old_eeAddress;
    // Cдесь сортировка будет по введённой линии и дням показ (Если дней введённых меньше чем даёт текущая дата)

  } //Если введённые дни меньше дня сегодняшнего. Вывод по введённой линии и кол-ву дней

  else if (Days > TodayDay && Days <= 30)
  { //Если введённые дни с BT больше сегодняшнего дня но меньше или равно 30. И это не конец года ( надо обработать )
#ifdef SendBT_Tubler
    Serial3.print(F("Будет выведена линия:"));
    Serial3.print(Line);
    Serial3.print(F(" Принято кол-во дней:"));
    Serial3.println(Days);
#else
    Serial.print(F("Будет выведена линия:"));
    Serial.print(Line);
    Serial.print(F(" Принято кол-во дней:"));
    Serial.println(Days);
#endif
    int8_t ZaxvatDayLastMonth; //Сколько дней надо захватить в прошлом месяце
    if (TodayMonth != 1)
    {
      int DayOt = TodayDay - Days; //DayOt =-7 //Сколько дней захватить надо в прошлом месяце [считаем по модулю]
      //Serial.print("TodayDay");Serial.print(TodayDay);     Serial.print(" Days");Serial.print(Days);      Serial.print(" DayOt");Serial.println(DayOt);
      ZaxvatDayLastMonth = MonthArr[TodayMonth - 1] + DayOt; // Узнали с какого дня прошлого месяца будет начинать выводится информация
    }
    else
    {
      int DayOt = TodayDay - Days; //DayOt =-7 //Сколько дней захватить надо в прошлом месяце [считаем по модулю]
      //Serial.print("TodayDay");Serial.print(TodayDay);     Serial.print(" Days");Serial.print(Days);      Serial.print(" DayOt");Serial.println(DayOt);
      ZaxvatDayLastMonth = MonthArr[12] + DayOt; // Узнали с какого дня прошлого месяца будет начинать выводится информация
    }
    if (TodayMonth != 1)
    { // Если сейчас не первый месяц года (прикол с переходом через год - надо уменьшить год)
#ifdef SendBT_Tubler
      Serial3.print(F("Будут выведены данные от "));
      Serial3.print(ZaxvatDayLastMonth);
      Serial3.print(".");
      Serial3.print(TodayMonth - 1);
      Serial3.print(".");
      Serial3.print(TodayYear);
      Serial3.print(" До ");
      Serial3.print(TodayDay);
      Serial3.print(".");
      Serial3.print(TodayMonth);
      Serial3.print(".");
      Serial3.println(TodayYear);
#else
      Serial.print(F("Будут выведены данные от "));
      Serial.print(ZaxvatDayLastMonth);
      Serial.print(".");
      Serial.print(TodayMonth - 1);
      Serial.print(".");
      Serial.print(TodayYear);
      Serial.print(" До ");
      Serial.print(TodayDay);
      Serial.print(".");
      Serial.print(TodayMonth);
      Serial.print(".");
      Serial.println(TodayYear);
#endif
    }
    else
    { // в строке отсчёт от - уменьшить год на 1цу
#ifdef SendBT_Tubler
      Serial3.print(F("Будут выведены данные от "));
      Serial3.print(ZaxvatDayLastMonth);
      Serial3.print(".");
      Serial3.print(12);
      Serial3.print(".");
      Serial3.print(TodayYear - 1);
      Serial3.print(" До ");
      Serial3.print(TodayDay);
      Serial3.print(".");
      Serial3.print(TodayMonth);
      Serial3.print(".");
      Serial3.println(TodayYear);
#else // Тут переделать
      Serial.print(F("Будут выведены данные от "));
      Serial.print(ZaxvatDayLastMonth);
      Serial.print(".");
      Serial.print(12);
      Serial.print(".");
      Serial.print(TodayYear - 1);
      Serial.print(" До ");
      Serial.print(TodayDay);
      Serial.print(".");
      Serial.print(TodayMonth);
      Serial.print(".");
      Serial.println(TodayYear);
#endif
    }

    //Cюда вставляем вывод если сейчас не первый месяц года
    if (TodayMonth != 1)
    { // Если сейчас не первый месяц года
      // Cдесь сортировка будет по введённой линии и дням показ (Если дней введённых меньше чем даёт текущая дата)
      int old_eeAddress = eeAddress; // Присваиваем переменной old_eeAddress а чтоб не сбить ползунок а затем вернём всё назад
      eeAddress = 10;                //Устанавливаем ползунок в начале адресов для чтения
      uint16_t countPodchet = 0;     // Временная переменная чтобы обьявить сколько же раз за заданный период считалась метка
      for (int i = 1; i <= AllMemoryExtEE1_7Yach / 3; i++)
      {
        //Serial.print("=== Начало цикла Адрес контроль в цикле: ==="); Serial.println(eeAddress);
        //Проверяем соответствует ли считанная строка нашим параметрам
        bool GoNext = false; // Разрешает или запрещает проход к секции вывода
        byte ReadLine = readEEPROM(rom, eeAddress);
        eeAddress += 1;       //Считываем линию
        if (ReadLine == Line) //Проверяем соответствие считанной линии тому что мы попросили показать по блютуз.Если да то проверяем дальше
        {
          //Serial.print("Проверка считанной линии:"); Serial.println(ReadLine);
          byte ReadDay = readEEPROM(rom, eeAddress);
          eeAddress += 1; //Считываем считанный из eeprom день
          byte ReadMonth = readEEPROM(rom, eeAddress);
          eeAddress += 1;                             //Считываем считанный из eeprom месяц
          byte ReadYear = readEEPROM(rom, eeAddress); //Считываем считанный из eeprom год
          //Serial.println();
          //Serial.print("ReadDay:"); Serial.print(ReadDay);              Serial.print(" TodayDay:"); Serial.println(TodayDay);
          //Serial.print("ReadMonth:"); Serial.print(ReadMonth);          Serial.print(" TodayMonth:"); Serial.println(TodayMonth);
          //Serial.print("ReadYear:"); Serial.print(ReadYear);            Serial.print(" TodayYear:"); Serial.println(TodayYear);

          //* Cлучай если сейчас не первый месяц года. Прочитать верхнюю половину
          if (ReadYear == TodayYear &&
              ReadMonth == TodayMonth &&
              ReadDay <= TodayDay && ReadDay > 0)
          {                //Если считанный год и месяц совпали с текущим и считанный день меньше или равен текущему и считанный день больше текущий день - минус заданный из BT день
            GoNext = true; // Разрешить проход
            //Serial.print("GoNext= true");    Serial.print(" eeAddress:"); Serial.println(eeAddress);
            eeAddress -= 3;
            countPodchet++; // Serial.println("countPodchet++");
          }
          //* Cлучай если сейчас не первый месяц года. Прочитать нижнюю половину
          //  /*
          else if (ReadYear == TodayYear &&         // В этом году
                   ReadMonth == (TodayMonth - 1) && // Копаемся в прошлом месяце
                   ReadDay >= ZaxvatDayLastMonth)
          {                // От захваченного дня до конца месяца прошлого
            GoNext = true; // Разрешить проход
            eeAddress -= 3;
            countPodchet++;
          }
          //  */
          else
          {
            eeAddress += 4;
            GoNext = false;
            //Serial.print("Выходим из else с ползунком:"); Serial.println(eeAddress);
          }
        }
        else
        {
          eeAddress -= 1;
          eeAddress += 7;
        } //Если линия не та что мы хотели вывести то откатить считанный адрес. И перепрыгнуть на следущую ячейку данных
          //Проверяем соответствует ли считанная строка нашим параметрам. Если да то GoNext cтановится true
        if (GoNext == true)
        {
          //Serial.print("GoNext eeAddress:"); Serial.println(eeAddress);Serial.print("");
          eeAddress += 1; // display to confirm

          byte ReadDay = readEEPROM(rom, eeAddress);
          eeAddress += 1;
          byte ReadMonth = readEEPROM(rom, eeAddress);
          eeAddress += 1;
          byte ReadYear = readEEPROM(rom, eeAddress);
          eeAddress += 1;

          byte ReadHour = readEEPROM(rom, eeAddress);
          eeAddress += 1;
          byte ReadMin = readEEPROM(rom, eeAddress);
          eeAddress += 1;
          byte ReadSec = readEEPROM(rom, eeAddress);
          eeAddress += 1;
#ifdef SendBT_Tubler
          Serial3.print("#");
          Serial3.print(i);
          Serial3.print(" ");
          Serial3.print(ReadLine, DEC);
          Serial3.print(" ");
          Serial3.print(ReadDay, DEC);
          Serial3.print(".");
          Serial3.print(ReadMonth, DEC);
          Serial3.print(".");
          Serial3.print(ReadYear, DEC);
          Serial3.print(" ");
          Serial3.print(ReadHour, DEC);
          Serial3.print(":");
          Serial3.print(ReadMin, DEC);
          Serial3.print(":");
          Serial3.println(ReadSec, DEC);
#else
          Serial.print("#");
          Serial.print(i);
          Serial.print(" ");
          Serial.print(ReadLine, DEC);
          Serial.print(" ");
          Serial.print(ReadDay, DEC);
          Serial.print(".");
          Serial.print(ReadMonth, DEC);
          Serial.print(".");
          Serial.print(ReadYear, DEC);
          Serial.print(" ");
          Serial.print(ReadHour, DEC);
          Serial.print(":");
          Serial.print(ReadMin, DEC);
          Serial.print(":");
          Serial.println(ReadSec, DEC);
#endif
        }
        //Serial.print("=== Конец цикла Адрес контроль в цикле: ==="); Serial.println(eeAddress);
      }
#ifdef SendBT_Tubler
      Serial3.print("Кол-во найденных проходов:");
      Serial3.println(countPodchet);
#else
      Serial.print("Кол-во найденных проходов:");
      Serial.println(countPodchet);
#endif
      eeAddress = old_eeAddress;
      // Cдесь сортировка будет по введённой линии и дням показ (Если дней введённых меньше чем даёт текущая дата)
    } // Если сейчас не первый месяц года

    else
    {                                       // Если сейчас ПЕРВЫЙ месяц года
                                            // Cдесь сортировка будет по введённой линии и дням показ (Если дней введённых меньше чем даёт текущая дата)
      static int old_eeAddress = eeAddress; // Присваиваем переменной old_eeAddress а чтоб не сбить ползунок а затем вернём всё назад
      eeAddress = 10;                       //Устанавливаем ползунок в начале адресов для чтения
      uint16_t countPodchet = 0;            // Временная переменная чтобы обьявить сколько же раз за заданный период считалась метка
      for (int i = 1; i <= AllMemoryExtEE1_7Yach; i++)
      {
        //Serial.print("=== Начало цикла Адрес контроль в цикле: ==="); Serial.println(eeAddress);
        //Проверяем соответствует ли считанная строка нашим параметрам
        bool GoNext = false; // Разрешает или запрещает проход к секции вывода
        byte ReadLine = readEEPROM(rom, eeAddress);
        eeAddress += 1;       //Считываем линию
        if (ReadLine == Line) //Проверяем соответствие считанной линии тому что мы попросили показать по блютуз.Если да то проверяем дальше
        {
          //Serial.print("Проверка считанной линии:"); Serial.println(ReadLine);
          byte ReadDay = readEEPROM(rom, eeAddress);
          eeAddress += 1; //Считываем считанный из eeprom день
          byte ReadMonth = readEEPROM(rom, eeAddress);
          eeAddress += 1;                             //Считываем считанный из eeprom месяц
          byte ReadYear = readEEPROM(rom, eeAddress); //Считываем считанный из eeprom год
          //Serial.println();
          //Serial.print("ReadDay:"); Serial.print(ReadDay);              Serial.print(" TodayDay:"); Serial.println(TodayDay);
          //Serial.print("ReadMonth:"); Serial.print(ReadMonth);          Serial.print(" TodayMonth:"); Serial.println(TodayMonth);
          //Serial.print("ReadYear:"); Serial.print(ReadYear);            Serial.print(" TodayYear:"); Serial.println(TodayYear);

          //* Cлучай если сейчас ПЕРВЫЙ месяц года. Прочитать верхнюю половину. То есть все даты с начала текущего года
          if (ReadYear == TodayYear &&   // В этом году
              ReadMonth == TodayMonth && // Копаемся в текущем месяце
              ReadDay <= TodayDay && ReadDay > 0)
          {                //Если считанный год и месяц совпали с текущим и считанный день меньше или равен текущему и считанный день больше текущий день - минус заданный из BT день
            GoNext = true; // Разрешить проход
            //Serial.print("GoNext= true");    Serial.print(" eeAddress:"); Serial.println(eeAddress);
            eeAddress -= 3;
            countPodchet++; // Serial.println("countPodchet++");
          }
          //* Cлучай если сейчас ПЕРВЫЙ месяц года. Прочитать нижнюю половину
          //  /*
          else if (ReadYear == (TodayYear - 1) && // В прошлом году
                   ReadMonth == 12 &&             // Копаемся в последнем месяце прошлого года
                   ReadDay >= ZaxvatDayLastMonth)
          {                // От захваченного дня до конца последнего месяца прошлого года
            GoNext = true; // Разрешить проход
            eeAddress -= 3;
            countPodchet++;
          }
          //  */
          else
          {
            eeAddress += 4;
            GoNext = false;
            //Serial.print("Выходим из else с ползунком:"); Serial.println(eeAddress);
          }
        }
        else
        {
          eeAddress -= 1;
          eeAddress += 7;
        } //Если линия не та что мы хотели вывести то откатить считанный адрес. И перепрыгнуть на следущую ячейку данных
          //Проверяем соответствует ли считанная строка нашим параметрам. Если да то GoNext cтановится true
        if (GoNext == true)
        {
          //Serial.print("GoNext eeAddress:"); Serial.println(eeAddress);Serial.print("");
          eeAddress += 1; // display to confirm

          byte ReadDay = readEEPROM(rom, eeAddress);
          eeAddress += 1;
          byte ReadMonth = readEEPROM(rom, eeAddress);
          eeAddress += 1;
          byte ReadYear = readEEPROM(rom, eeAddress);
          eeAddress += 1;

          byte ReadHour = readEEPROM(rom, eeAddress);
          eeAddress += 1;
          byte ReadMin = readEEPROM(rom, eeAddress);
          eeAddress += 1;
          byte ReadSec = readEEPROM(rom, eeAddress);
          eeAddress += 1;
#ifdef SendBT_Tubler
          Serial3.print("#");
          Serial3.print(i);
          Serial3.print(" ");
          Serial3.print(ReadLine, DEC);
          Serial3.print(" ");
          Serial3.print(ReadDay, DEC);
          Serial3.print(".");
          Serial3.print(ReadMonth, DEC);
          Serial3.print(".");
          Serial3.print(ReadYear, DEC);
          Serial3.print(" ");
          Serial3.print(ReadHour, DEC);
          Serial3.print(":");
          Serial3.print(ReadMin, DEC);
          Serial3.print(":");
          Serial3.println(ReadSec, DEC);
#else
          Serial.print("#");
          Serial.print(i);
          Serial.print(" ");
          Serial.print(ReadLine, DEC);
          Serial.print(" ");
          Serial.print(ReadDay, DEC);
          Serial.print(".");
          Serial.print(ReadMonth, DEC);
          Serial.print(".");
          Serial.print(ReadYear, DEC);
          Serial.print(" ");
          Serial.print(ReadHour, DEC);
          Serial.print(":");
          Serial.print(ReadMin, DEC);
          Serial.print(":");
          Serial.println(ReadSec, DEC);
#endif
        }
        //Serial.print("=== Конец цикла Адрес контроль в цикле: ==="); Serial.println(eeAddress);
      }
#ifdef SendBT_Tubler
      Serial3.print("Кол-во найденных проходов:");
      Serial3.println(countPodchet);
#else
      Serial.print("Кол-во найденных проходов:");
      Serial.println(countPodchet);
#endif
      eeAddress = old_eeAddress;
      // Cдесь сортировка будет по введённой линии и дням показ (Если дней введённых меньше чем даёт текущая дата)
    } // Если сейчас ПЕРВЫЙ месяц года
  }

  else
  {
#ifdef SendBT_Tubler
    Serial3.println(F("Не больше 30ти дней! Введи 30 или меньше"));
#else
    Serial.println(F("Не больше 30ти дней! Введи 30 или меньше"));
#endif
  }
}

byte writeEEPROM(byte device, unsigned int addr, byte *data, byte len)
{
  byte err;
  byte counter;

  if (len > BUFFER_LENGTH) // 32 (in Wire.h)
    return 0xFF;           // too long

  Wire.beginTransmission(device);
  Wire.write((byte)(addr >> 8));   // high order byte
  Wire.write((byte)(addr & 0xFF)); // low-order byte
  Wire.write(data, len);
  err = Wire.endTransmission();

  if (err != 0)
    return err; // cannot write to device

  // wait for write to finish by sending address again
  //  ... give up after 100 attempts (1/10 of a second)
  for (counter = 0; counter < 100; counter++)
  {
    delayMicroseconds(300); // give it a moment
    Wire.beginTransmission(device);
    Wire.write((byte)(addr >> 8));   // high order byte
    Wire.write((byte)(addr & 0xFF)); // low-order byte
    err = Wire.endTransmission();
    if (err == 0)
      break;
  }

  return err;

} // end of writeEEPROM

// write one byte to device, returns non-zero on error
byte writeEEPROM(byte device, unsigned int addr, byte data)
{
  return writeEEPROM(device, addr, &data, 1);
} // end of writeEEPROM

// read len (max 32) bytes from device, returns non-zero on error
//  return code: 0xFF means buffer too long
//               0xFE means device did not return all requested bytes
//             other: other error (eg. device not present)

// Note that if reading multiple bytes the address plus
//  length must not cross a 64-byte boundary or it will "wrap"

byte readEEPROM(byte device, unsigned int addr, byte *data, byte len)
{
  byte err;
  byte counter;

  if (len > BUFFER_LENGTH) // 32 (in Wire.h)
    return 0xFF;           // too long

  Wire.beginTransmission(device);
  Wire.write((byte)(addr >> 8));   // high order byte
  Wire.write((byte)(addr & 0xFF)); // low-order byte
  err = Wire.endTransmission();

  if (err != 0)
    return err; // cannot read from device

  // initiate blocking read into internal buffer
  Wire.requestFrom(device, len);

  // pull data out of Wire buffer into our buffer
  for (counter = 0; counter < len; counter++)
  {
    data[counter] = Wire.read();
  }

  return 0; // OK
} // end of readEEPROM

// read one byte from device, returns 0xFF on error
byte readEEPROM(byte device, unsigned int addr)
{
  byte temp;

  if (readEEPROM(device, addr, &temp, 1) == 0)
    return temp;

  return 0xFF;

} // end of readEEPROM

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