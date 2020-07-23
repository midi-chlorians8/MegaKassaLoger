//Кнопки и счётчики срабатываний
// Пакет для линии 1
#define Line1_PIN1 2
#define Line1_PIN2 3  
uint16_t Line1_countToday=0; 
String L1DataStr;

unsigned long L1TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L1TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L1OneZjmyakBut1=false; 
bool L1OneZjmyakBut2=false; 
unsigned long L1WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L1CanReadBool;
// Пакет для линии 1

// Пакет для линии 2
#define Line2_PIN1 4
#define Line2_PIN2 5  
uint16_t Line2_countToday=0; 
String L2DataStr;

unsigned long L2TimingButt1; // Переменная для записи времени когда нажата кнопка 1
unsigned long L2TimingButt2; // Переменная для записи времени когда нажата кнопка 2

bool L2OneZjmyakBut1=false; 
bool L2OneZjmyakBut2=false; 
unsigned long L2WaitObrabotkaButt; //Переменная хранит точку отсчёта от которой 300мсек отсчитываются при входе в анализ направления движения

bool L2CanReadBool;
// Пакет для линии 2
//Кнопки и счётчики срабатываний

// RTC
String MyDateTimeStr;
String MyMonth;
#include <Wire.h> // must be included here so that Arduino library object file references work
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
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
String teststring = "Hello User. Введи запрос в формате l2d2";

byte EnteredLine; //Какую мы ввели линию чтоб посмотреть распечатку лога с неё
uint8_t posL;     //Позиция для парсинга
byte EnteredDays; //Сколько мы ввели дней чтобы увидеть за сколько дней давать лог
uint8_t posD;     //Позиция для парсинга
#define resetPin  12
// BT

