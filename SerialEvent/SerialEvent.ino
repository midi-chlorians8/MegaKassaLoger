/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent
*/

String inputStringHard = "";         // a String to hold incoming data
bool stringCompleteHard = false;  // whether the string is complete

String inputStringBT = "";         // a String to hold incoming data
bool stringCompleteBT = false;  // whether the string is complete

// Parsing
byte EnteredLine; //Какую мы ввели линию чтоб посмотреть распечатку лога с неё
uint8_t posL;     //Позиция для парсинга
byte EnteredDays; //Сколько мы ввели дней чтобы увидеть за сколько дней давать лог
uint8_t posD;     //Позиция для парсинга
// Parsing
void setup() {
  // initialize serial:
  Serial.begin(115200);
  Serial3.begin(115200);
  // reserve 200 bytes for the inputString:
  inputStringHard.reserve(200);
  inputStringBT.reserve(200);
}

void loop() {




  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read();
    // add it to the inputString:
    inputStringBT += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringCompleteBT = true;
    }
  }
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputStringHard += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringCompleteHard = true;
    }
  }

  if (stringCompleteBT) {
    Serial.println(inputStringBT);
    if (inputStringBT.substring(0, 1) == "t" && inputStringBT.length() == 3) { //При встреченном символе перевода строки
      Serial3.print(F("Текущее время: ")); Serial3.print(123);  Serial3.print(F(" Ползунок на адресе: ")); Serial3.println(456);
    }

     if (inputStringBT.substring(0, 1) == "a") {
      Serial3.println (); Serial3.println(F("Печать всех данных:"));
    }
    if (inputStringBT.substring(0, 1) == "e") { //Удалить всё
      Serial3.println (); Serial3.println(F("Начало полного стирания:"));
    }
    Serial.print("inputStringBT.length() "); Serial.println( inputStringBT.length() );
l1
    // Разборка линия дни стринга
    if (inputStringBT.substring(0, 1) == "l") {
      posL = inputStringBT.indexOf('l');
      posD = inputStringBT.indexOf('d');
      EnteredLine = inputStringBT.substring(posL + 1, posD).toInt();
      EnteredDays = inputStringBT.substring(posD + 1, inputStringBT.length() ).toInt();

      //Serial.print(F("EnteredLine:")); Serial.print(EnteredLine);     Serial.print(F(" EnteredDays:")); Serial.println(EnteredDays);
      Serial3.print(F("Я читаю из памяти линию: ")); Serial3.print(EnteredLine);  Serial3.print(F(" Лог за: ")); Serial3.print(EnteredDays); Serial3.println(F("дней"));
    }
    // Разборка линия дни стринга

    // clear the string:
    inputStringBT = "";
    stringCompleteBT = false;
  }



  if (stringCompleteHard) {
    if (inputStringHard == "t\n") { //При встреченном символе перевода строки
      Serial.print(F("Текущее время: ")); Serial.print(123);  Serial.print(F(" Ползунок на адресе: ")); Serial.println(456);
    }
    if (inputStringHard == "a\n") {
      Serial.println (); Serial.println(F("Печать всех данных:"));
    }
    if (inputStringHard == "e\n") { //Удалить всё
      Serial.println (); Serial.println(F("Начало полного стирания:"));
    }
   
    Serial.print("inputStringHard.length() "); Serial.println( inputStringHard.length() );   //Serial.println(inputStringHard);

    // Разборка линия дни стринга
    if (inputStringHard.substring(0, 1) == "l") {
      posL = inputStringHard.indexOf('l');
      posD = inputStringHard.indexOf('d');
      EnteredLine = inputStringHard.substring(posL + 1, posD).toInt();
      EnteredDays = inputStringHard.substring(posD + 1, inputStringHard.length() ).toInt();

      Serial.print(F("EnteredLine:")); Serial.print(EnteredLine);     Serial.print(F(" EnteredDays:")); Serial.println(EnteredDays);
      //Serial3.print(F("Я читаю из памяти линию: ")); Serial3.print(EnteredLine);  Serial3.print(F(" Лог за: ")); Serial3.print(EnteredDays); Serial3.println(F("дней"));
    }
    // Разборка линия дни стринга

    // clear the string:
    inputStringHard = "";
    stringCompleteHard = false;
  }






}


/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
