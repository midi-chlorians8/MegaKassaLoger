#include <Arduino.h>
#include "GyverButton.h" 

#define Line1_PIN1 2
#define Line1_PIN2 3  

GButton butt1(PIN2);
GButton butt2(PIN3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); while(!Serial){}
  Serial3.begin(9600);  //while(!Serial3){}
  Serial3.println("BT Started");
}

void loop() {
    butt1.tick();   butt2.tick(); //Опрос обоих переключатилей линии 1
      if (butt1.isSingle()) Serial.println("Single butt1");     // проверка на один клик
      if (butt2.isSingle()) Serial.println("Single butt2");     // проверка на один клик



      
  int i;
  i++;
  i++;
  i+=5;
  Serial.println(i);
}