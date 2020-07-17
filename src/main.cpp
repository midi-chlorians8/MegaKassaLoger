#include <Arduino.h>
#include <Definition.h>

// RTC
String MyDateTimeStr;
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    //Serial.print(datestring);
    MyDateTimeStr=datestring; // Забираю себе дату и время
}
// RTC
void setup() {
  Serial.begin(115200); while(!Serial){}
  //Serial3.begin(9600);  //while(!Serial3){}  // Serial3.println("BT Started");

  

  //Кнопки и счётчики срабатываний
  pinMode(Line1_PIN1,INPUT_PULLUP); pinMode(Line1_PIN2,INPUT_PULLUP);
  Serial.print("TimingButt1:");Serial.print(TimingButt1);  Serial.print(" TimingButt2:");Serial.println(TimingButt2);
  Serial.println();Serial.println();Serial.println();
  //Кнопки и счётчики срабатываний

  // RTC
  Serial.print("compiled: ");    Serial.print(__DATE__); Serial.println(__TIME__);
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
}


void ObrabotkaOneSide(String NameLine,int8_t pin,int8_t pin2,uint16_t& Line_countToday){ //Функция должна при нажатии последовательно кнопки 1, а затем кнопки 2 увеличить глобальный счётчик прохода в линии
//void ObrabotkaOneSide(int8_t pin,int8_t pin2,uint16_t& Line_countToday){ //Функция должна при нажатии последовательно кнопки 1, а затем кнопки 2 увеличить глобальный счётчик прохода в линии
 
 static unsigned long WaitObrabotkaButt; //Переменная для того чтоб убрать делей. В деле при обработке после нажатия обеих кнопок
 static bool CanReadBool = true;
 
 //Ввод значений нажатия кнопки. Результат нажатия були OneZjmyakBut1 и OneZjmyakBut2 
 if(CanReadBool == true){ //Если разрешено читать кнопки
    if(digitalRead(pin) == 0){ // Если нажата кнопка 1
      if(OneZjmyakBut1==false){
      TimingButt1=millis(); // Присвоить значение таймера в переменную
      //Serial.print("[pin]TimingButt1:");Serial.print(TimingButt1);Serial.print(" TimingButt2:");Serial.println(TimingButt2);
      OneZjmyakBut1=true;
      }
  }
    if(digitalRead(pin2) == 0){// Если нажата кнопка 2
      if(OneZjmyakBut2==false){
      TimingButt2=millis(); // Присвоить значение таймера в переменную
      //Serial.print("[pin2]TimingButt1:");Serial.print(TimingButt1);Serial.print(" TimingButt2:");Serial.println(TimingButt2);
      OneZjmyakBut2=true;
    }
  }
 }                      //Если разрешено читать кнопки
 //Ввод значений нажатия кнопки. Результат нажатия були OneZjmyakBut1 и OneZjmyakBut2 
 
 //Обработка значений. Прибавка счётчика нажатий
   if(OneZjmyakBut1==true && OneZjmyakBut2 == true){ 
   CanReadBool=false; // Запретить чтение кнопок
      if( (TimingButt1-TimingButt2)<0  ){
        Line_countToday++;
        /*
        //Serial.print(F("Proxod Dobavlen:")); Serial.print(F("TB1-TB2)<0 "));
        Serial.print(NameLine); Serial.print(F("Line_countToday:")); 
        Serial.print(Line_countToday); Serial.print(" ");
        Serial.print(MyDateTimeStr); Serial.println();
        */
        L1DataStr=NameLine + Line_countToday + " " + MyDateTimeStr;
        Serial.print("L1DataStr");Serial.println(L1DataStr);
      }
      if( (TimingButt1-TimingButt2)>0  ){
      Serial.print("Proxod v obratnyu storonu:"); Serial.println("TimingButt1-TimingButt2)>0");Serial.println();
      }
      OneZjmyakBut1=false; OneZjmyakBut2=false; // Перезаряд
      TimingButt1=0;       TimingButt2=0;       // Перезаряд
      WaitObrabotkaButt=millis(); // Присваиваим точку отсчёта переменной от которой будет отсчёт для активации буля возможности чтения кнопок
 //Обработка значений. Прибавка счётчика нажатий
}
 if (millis() - WaitObrabotkaButt > 300){ // Вместо 300 подставьте нужное вам значение паузы 
       CanReadBool=true;      
       WaitObrabotkaButt = millis(); //Serial.println ("10 seconds");
 }
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime(); // Обновляем время
  printDateTime(now); // Передаём изменённое время в функцию откуда извлекаем его сами

  ObrabotkaOneSide("L1:",Line1_PIN1,Line1_PIN2,Line1_countToday); // захват прохода в одну сторону. Уведичение счётчика переданной линии
  //ObrabotkaOneSide(Line1_PIN1,Line1_PIN2,Line1_countToday);
}
















