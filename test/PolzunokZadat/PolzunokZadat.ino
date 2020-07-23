/*
String Date_time_line_count =  "L1:999 07/19/2020 14:12:08";
String Date_time_line_count2 = "L2:888 07/19/2020 18:19:55";
String Date_time_line_count3 = "L6:556 07/19/2020 11:12:33";
String Date_time_line_count4 = "L7:777 07/19/2020 11:12:33";
*/
/*
String Date_time_line_count =  "L1:999";
String Date_time_line_count2 = "L2:888";
String Date_time_line_count3 = "L6:556";
String Date_time_line_count4 = "L7:777";
*/
String EeAdrStr = "10";
// Written by Nick Gammon
// February 2011

// Note: maximum address is 0x7FFF (32 Kbytes)

#include <Wire.h>
const byte rom = 0x50;    // Address of 24LC256 eeprom chip

void setup (void)
{
  /*
  char Date_time_line_countBuf[27];  Date_time_line_count.toCharArray(Date_time_line_countBuf, 27);
  char Date_time_line_countBuf2[27];  Date_time_line_count2.toCharArray(Date_time_line_countBuf2, 27);
  char Date_time_line_countBuf3[27];  Date_time_line_count3.toCharArray(Date_time_line_countBuf3, 27);
  char Date_time_line_countBuf4[27];  Date_time_line_count4.toCharArray(Date_time_line_countBuf4, 27);
*/
  char EeAdrStrBuf[6];  EeAdrStr.toCharArray(EeAdrStrBuf, 6);
  Serial.begin (115200);   // debugging
  Wire.begin ();


  byte MyArrayData[6]; //Обозначили размер byte коробки в которую вписываем сhar array
  // Первый пошёл
  for (int i=0; i < sizeof(MyArrayData); i++) {
    MyArrayData[i] = byte(EeAdrStrBuf[i] ); //Преобразование массива сhar в массив byte
  }
  writeEEPROM (rom, 1, MyArrayData, sizeof(MyArrayData) ); // Запись byte массива
  // Первый пошёл
  /*
  // Второй пошёл
  for (int i=0; i < sizeof(Date_time_line_countBuf2); i++) {
    MyArrayData[i] = byte(Date_time_line_countBuf2[i] ); //Преобразование массива сhar в массив byte
  }
   writeEEPROM (rom, (100 + 28), MyArrayData, sizeof( MyArrayData) );
  // Второй пошёл

  // Третий пошёл
  for (int i=0; i < sizeof(Date_time_line_countBuf3); i++) {
    MyArrayData[i] = byte(Date_time_line_countBuf3[i] ); //Преобразование массива сhar в массив byte
  }
   writeEEPROM (rom, (100 + 28+28), MyArrayData, sizeof(MyArrayData) );
  // Третий пошёл

  // Четвёртый пошёл
 for (int i=0; i < sizeof(Date_time_line_countBuf4); i++) {
    MyArrayData[i] = byte(Date_time_line_countBuf4[i] ); //Преобразование массива сhar в массив byte
  }
   writeEEPROM (rom, (100 + 28+28+28), MyArrayData, sizeof(MyArrayData) );
  // Четвёртый пошёл
  */
  //byte ReadPolzunArr [sizeof MyArrayData];
  byte ReadPolzunArr [sizeof MyArrayData];
  byte err;
  Serial.println ("I read");
  // Первый прочитался
  err= readEEPROM (rom, 1, ReadPolzunArr, sizeof(ReadPolzunArr) );
  Serial.println ((char *) ReadPolzunArr);  // display to confirm
  // Первый прочитался
/*
  // Второй прочитался
  err = readEEPROM (rom, (100 + 28), test, sizeof(test) );
  Serial.println ((char *) test);  // display to confirm
  // Второй прочитался

  // Третий прочитался
 err = readEEPROM (rom, (100 + 28 + 28), test, sizeof(test) );
  Serial.println ((char *) test);  // display to confirm
  // Третий прочитался

  // Четвёртый прочитался
 err = readEEPROM (rom, (100 + 28 + 28 +28), test, sizeof(test) );
  Serial.println ((char *) test);  // display to confirm
  // Третий прочитался
*/


  /*
     //Serial.print("sizeof (hello):"); Serial.println (sizeof (hello) );
    byte hello2 [] = "Ballo, qorld!";
    writeEEPROM (rom, 1 + 14, hello2, sizeof hello2);

    byte test2 [sizeof hello2];
    byte err2 = readEEPROM (rom, 1 + 14, test2, sizeof test2);
    Serial.println ((char *) test2);  // display to confirm
  */
}  // end of setup

void loop() {}  // no main loop

  // test: write a string to address 0x1000
  //  byte hello [] = "Hello, world!";
// write len (max 32) bytes to device, returns non-zero on error
//  return code: 0xFF means buffer too long
//             other: other error (eg. device not present)

// Note that if writing multiple bytes the address plus
//  length must not cross a 64-byte boundary or it will "wrap"

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
