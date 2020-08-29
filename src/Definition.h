//Кнопки и счётчики срабатываний
// Пакет для линии 1
#define Line1_PIN1 2
#define Line1_PIN2 3  
//uint16_t Line1_countToday=0; //String L1DataStr;

unsigned long L1TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L1TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L1OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L1OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L1WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L1CanReadBool;
// Пакет для линии 1

// Пакет для линии 2
#define Line2_PIN1 4
#define Line2_PIN2 5  
//uint16_t Line2_countToday=0; //String L2DataStr;

unsigned long L2TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L2TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L2OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L2OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L2WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L2CanReadBool;
// Пакет для линии 2

// Пакет для линии 3
#define Line3_PIN1 A0
#define Line3_PIN2 A1 
//uint16_t Line2_countToday=0; //String L3DataStr;

unsigned long L3TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L3TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L3OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L3OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L3WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L3CanReadBool;
// Пакет для линии 3

// Пакет для линии 4
#define Line4_PIN1 A2
#define Line4_PIN2 A3 

unsigned long L4TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L4TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L4OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L4OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L4WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L4CanReadBool;
// Пакет для линии 4

// Пакет для линии 5
#define Line5_PIN1 A4
#define Line5_PIN2 A5 

unsigned long L5TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L5TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L5OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L5OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L5WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L5CanReadBool;
// Пакет для линии 5

// Пакет для линии 6
#define Line6_PIN1 A6
#define Line6_PIN2 A7 

unsigned long L6TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L6TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L6OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L6OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L6WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L6CanReadBool;
// Пакет для линии 6

// Пакет для линии 7
#define Line7_PIN1 A8
#define Line7_PIN2 A9 

unsigned long L7TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L7TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L7OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L7OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L7WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L7CanReadBool;
// Пакет для линии 7

// Пакет для линии 8
#define Line8_PIN1 A10
#define Line8_PIN2 A11 

unsigned long L8TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L8TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L8OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L8OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L8WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L8CanReadBool;
// Пакет для линии 8

// Пакет для линии 9
#define Line9_PIN1 A12
#define Line9_PIN2 A13 

unsigned long L9TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L9TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L9OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L9OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L9WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L9CanReadBool;
// Пакет для линии 9

// Пакет для линии 10
#define Line10_PIN1 53
#define Line10_PIN2 51 

unsigned long L10TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L10TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L10OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L10OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L10WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L10CanReadBool;
// Пакет для линии 10

// Пакет для линии 11
#define Line11_PIN1 47
#define Line11_PIN2 45 

unsigned long L11TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L11TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L11OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L11OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L11WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L11CanReadBool;
// Пакет для линии 11

// Пакет для линии 12
#define Line12_PIN1 43
#define Line12_PIN2 41 

unsigned long L12TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L12TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L12OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L12OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L12WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L12CanReadBool;
// Пакет для линии 12

// Пакет для линии 13
#define Line13_PIN1 39
#define Line13_PIN2 37 

unsigned long L13TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L13TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L13OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L13OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L13WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L13CanReadBool;
// Пакет для линии 13 

// Пакет для линии 14
#define Line14_PIN1 35
#define Line14_PIN2 33 

unsigned long L14TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L14TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L14OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L14OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L14WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L14CanReadBool;
// Пакет для линии 14

// Пакет для линии 15
#define Line15_PIN1 8
#define Line15_PIN2 9 

unsigned long L15TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L15TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L15OneZjmyakBut1=false; //Если нажата кнопка 1 буль = true
bool L15OneZjmyakBut2=false; //Если нажата кнопка 2 буль = true
unsigned long L15WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L15CanReadBool;
// Пакет для линии 15
//Кнопки и счётчики срабатываний

// RTC
String MyDateTimeStr;
String MyMonth;
#include <Wire.h> // must be included here so that Arduino library object file references work 47 45
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];
    snprintf_P(datestring,  countof(datestring), PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
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

void PrintDebug(); // Прототип
void Bluetooth();
void ReadLineDays(const byte& Line,const byte& Days);// для BT
void ReadAll();
byte writeEEPROM (byte device, unsigned int addr, byte * data, byte len );
byte writeEEPROM (byte device, unsigned int addr, byte data );
byte readEEPROM (byte device, unsigned int addr, byte * data, byte len );
byte readEEPROM (byte device, unsigned int addr );
void TmimgRefresh();
// BT
String inputStringHard = "";         // a String to hold incoming data
bool stringCompleteHard = false;  // whether the string is complete

String inputStringBT = "";         // a String to hold incoming data
bool stringCompleteBT = false;  // whether the string is complete
String teststring = "Hello User. Введи запрос в формате l2d2";

byte EnteredLine; //Какую мы ввели линию чтоб посмотреть распечатку лога с неё
uint8_t posL;     //Позиция для парсинга
byte EnteredDays; //Сколько мы ввели дней чтобы увидеть за сколько дней давать лог
uint8_t posD;     //Позиция для парсинга
//#define resetPin  12
// BT

void PinMode(){
  pinMode(Line1_PIN1,INPUT_PULLUP); pinMode(Line1_PIN2,INPUT_PULLUP);
  pinMode(Line2_PIN1,INPUT_PULLUP); pinMode(Line2_PIN2,INPUT_PULLUP);
  pinMode(Line3_PIN1,INPUT_PULLUP); pinMode(Line3_PIN2,INPUT_PULLUP);
  pinMode(Line4_PIN1,INPUT_PULLUP); pinMode(Line4_PIN2,INPUT_PULLUP);

  pinMode(Line5_PIN1,INPUT_PULLUP); pinMode(Line5_PIN2,INPUT_PULLUP);
  pinMode(Line6_PIN1,INPUT_PULLUP); pinMode(Line6_PIN2,INPUT_PULLUP);
  pinMode(Line7_PIN1,INPUT_PULLUP); pinMode(Line7_PIN2,INPUT_PULLUP);
  pinMode(Line8_PIN1,INPUT_PULLUP); pinMode(Line8_PIN2,INPUT_PULLUP);

  pinMode(Line9_PIN1,INPUT_PULLUP); pinMode(Line9_PIN2,INPUT_PULLUP);
  pinMode(Line10_PIN1,INPUT_PULLUP); pinMode(Line10_PIN2,INPUT_PULLUP);
  pinMode(Line11_PIN1,INPUT_PULLUP); pinMode(Line11_PIN2,INPUT_PULLUP);
  pinMode(Line12_PIN1,INPUT_PULLUP); pinMode(Line12_PIN2,INPUT_PULLUP);
 
  pinMode(Line13_PIN1,INPUT_PULLUP); pinMode(Line13_PIN2,INPUT_PULLUP);
  pinMode(Line14_PIN1,INPUT_PULLUP); pinMode(Line14_PIN2,INPUT_PULLUP);
  pinMode(Line15_PIN1,INPUT_PULLUP); pinMode(Line15_PIN2,INPUT_PULLUP);
}