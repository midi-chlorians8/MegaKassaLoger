#include <Arduino.h>
//#include "GyverButton.h" 

#define Line1_PIN1 2
#define Line1_PIN2 3  

//GButton butt1(Line1_PIN1);
//GButton butt2(Line1_PIN2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); while(!Serial){}
 // Serial3.begin(9600);  //while(!Serial3){}
 // Serial3.println("BT Started");
 pinMode(Line1_PIN1,INPUT_PULLUP);
 pinMode(Line1_PIN2,INPUT_PULLUP);
}



void loop() {
Serial.print("Line1Pin2:"); Serial.print(digitalRead(2));
Serial.print(" Line1Pin3:"); Serial.println(digitalRead(3));



}

