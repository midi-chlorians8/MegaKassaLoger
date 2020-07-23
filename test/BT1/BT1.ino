
// BT
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
String teststring = "Hello User. Введи запрос в формате l2d2";

byte EnteredLine; //Какую мы ввели линию чтоб посмотреть распечатку лога с неё
uint8_t posL;     //Позиция для парсинга
byte EnteredDays; //Сколько мы ввели дней чтобы увидеть за сколько дней давать лог
uint8_t posD;     //Позиция для парсинга
#define resetPin  12
// BT

void setup() {
  // BT
  digitalWrite(resetPin, HIGH);
  delay(200);
  // инициализируем цифровой пин в качестве выхода
  Serial3.begin(9600);
  pinMode(resetPin, OUTPUT);
  Serial3.println(teststring);
  inputString.reserve(200);
  // BT

  Serial.begin(115200);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}
  // BT
  

}

void loop() { // run over and over
 


  Bluetooth(); // Принимает при подключении s, перезагружает и готов к работе // BT
}


  void Bluetooth(){
  // BT
  static bool IsEnterLine = false; // Упомянуты ли линии в сообщении
  static bool IsEnterDay = false; // Упомянуты ли дни в сообщении
  static bool Endline = false; // Говорит нам о том что принятая строка закончилась
  if (Serial3.available() > 0) {
    Serial.println("*");
    char inChar = (char)Serial3.read();
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
    // Тут мы разбираем входящие цифры линии и дней
    // /*
    if (IsEnterLine == 1 && IsEnterDay == 1 && Endline == true) { //Если упомянуты линии дни и строка уже полностью у нас
      Serial.print("inputString:"); Serial.println(inputString);
      EnteredLine = inputString.substring(posL + 1, posD).toInt();
      EnteredDays = inputString.substring(posD + 1, inputString.length() ).toInt();
      Serial.print("EnteredLine:"); Serial.println(EnteredLine);
      Serial.print("EnteredDays:"); Serial.println(EnteredDays);
      Serial3.print("Я читаю из памяти линию: "); Serial3.print(EnteredLine);  Serial3.print(" Лог за: "); Serial3.print(EnteredDays); Serial3.println("дней");
      Endline = false; // Стока уже не полная мы обнуляем её
      inputString = ""; // Обнуление строки
      IsEnterLine = 0;   IsEnterDay = 0;
    }

  
  }
  // BT
  }





























/*
  void Bluetooth(){
  // BT

   if (Serial.available()) {
     char inChar = (char)Serial.read();
        if(inChar == 'p'){
          Serial.println();
          Serial.print(" inputString: "); Serial.print( inputString ); Serial.print(" posL="); Serial.print(posL);Serial.print(" posD="); Serial.println(posD);
          Serial.print("MyParce L:");Serial.println(inputString.substring(posL+1,posD) );
          Serial.print("MyParce D:");Serial.println(inputString.substring(posD+1,inputString.length() ) );

          Serial.println();
          inputString=""; //Обязательно в конце операций надо очистить строку. А то новые значения не перезаписываются
        }
             if(inChar == 'h'){
                  Serial.print("IsEnterLine:");Serial.println(IsEnterLine);
                   Serial.print("IsEnterDay:");Serial.println(IsEnterDay);
             }
              if(inChar == 's'){
               resetFunc();
               softReset();
             }
    }

  // BT

  }
*/

/*

void softReset() {
  asm volatile ("jmp 0");
}
*/




  // */
    // Serial.print("MyParce L:");Serial.println(inputString.substring(posL+1,posD) );
    // Тут мы разбираем входящие цифры линии и дней

/*


    if (inChar == 'z') { //Реакция на символ есть
      Serial.println("Symbol");
    }


  /*
  if (Serial.available()) {
    Serial3.write(Serial.read());
  }






*/


/*
    // Отладка
    if (Serial.available()) {
     char inChar = (char)Serial.read();
        if(inChar == 'p'){
          Serial.println();
          Serial.print(" inputString: "); Serial.print( inputString ); Serial.print(" posL="); Serial.print(posL);Serial.print(" posD="); Serial.println(posD);
          Serial.print("MyParce L:");Serial.println(inputString.substring(posL+1,posD) );
          Serial.print("MyParce D:");Serial.println(inputString.substring(posD+1,inputString.length() ) );

          Serial.println();
          inputString=""; //Обязательно в конце операций надо очистить строку. А то новые значения не перезаписываются
        }
    }
    // Отладка
*/
