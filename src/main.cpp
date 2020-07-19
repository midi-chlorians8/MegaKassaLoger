#include <Arduino.h>
#include <Definition.h>
//EEPROM
#include <EEPROM.h>

struct MyObject {
  byte NameLine;
  int Line_countToday;
  char Date_time[20];
};
int eeAddress = 0;   //Location we want the data to be put.
//EEPROM
void setup() {
  Serial.begin(19200); while(!Serial){}
  //Serial3.begin(9600);  //while(!Serial3){}  // Serial3.println("BT Started");

  //Кнопки и счётчики срабатываний
  pinMode(Line1_PIN1,INPUT_PULLUP); pinMode(Line1_PIN2,INPUT_PULLUP);
  pinMode(Line2_PIN1,INPUT_PULLUP); pinMode(Line2_PIN2,INPUT_PULLUP);
  Serial.print("TimingButt1:");Serial.print(L1TimingButt1);  Serial.print(" TimingButt2:");Serial.println(L1TimingButt2);
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


void ObrabotkaOneSide(String NameLine,int8_t pin,int8_t pin2,uint16_t& Line_countToday,bool& CanReadBool,unsigned long& TimingButtFirst,unsigned long& TimingButtSecond,bool& OneZjmyakButFirst,bool& OneZjmyakButSecond,unsigned long& WaitObrabotkaButt, String& DataStr){ //Функция должна при нажатии последовательно кнопки 1, а затем кнопки 2 увеличить глобальный счётчик прохода в линии

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
        Line_countToday++;
        
        //Serial.print(F("Proxod Dobavlen:")); Serial.print(F("TB1-TB2)<0 "));       Serial.print(NameLine); Serial.print(F("Line_countToday:"));        Serial.print(Line_countToday); Serial.print(" ");        Serial.print(MyDateTimeStr); Serial.println();
        
        DataStr=NameLine + Line_countToday + " " + MyDateTimeStr;
        Serial.print("DataStr");Serial.println(DataStr);
        // Тут можно подцепится запись в EEPROM
        MyObject customVar = {
         NameLine,
         65,
        "07/19/2020 14:11:39"
  };
        OneZjmyakButFirst=false; OneZjmyakButSecond=false; // Перезаряд
      }
      //if( (TimingButt1-TimingButt2)>0  ){
      if( TimingButtFirst > TimingButtSecond  ){
      Serial.print("Proxod v obratnyu storonu:"); //Serial.println("TimingButt1-TimingButt2)>0");Serial.println();
      }
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

unsigned long timingRefresh; // Переменная для хранения точки отсчета
void loop() {
if (millis() - timingRefresh > 1000){ // Вместо 10000 подставьте нужное вам значение паузы 
   RtcDateTime now = Rtc.GetDateTime(); // Обновляем время
   printDateTime(now); // Передаём изменённое время в функцию откуда извлекаем его сами
   timingRefresh = millis(); 
}

  ObrabotkaOneSide("L1:",Line1_PIN1,Line1_PIN2,Line1_countToday,L1CanReadBool  ,L1TimingButt1,L1TimingButt2,  L1OneZjmyakBut1,L1OneZjmyakBut2 ,L1WaitObrabotkaButt, L1DataStr); // захват прохода в одну сторону. Уведичение счётчика переданной линии
  ObrabotkaOneSide("L2:",Line2_PIN1,Line2_PIN2,Line2_countToday,L2CanReadBool  ,L2TimingButt1,L2TimingButt2,  L2OneZjmyakBut1,L2OneZjmyakBut2 ,L2WaitObrabotkaButt, L2DataStr); // захват прохода в одну сторону. Уведичение счётчика переданной линии
  
  //ObrabotkaOneSide(Line1_PIN1,Line1_PIN2,Line1_countToday);
  //PrintDebug();
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








