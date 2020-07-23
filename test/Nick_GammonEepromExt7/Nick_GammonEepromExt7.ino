
/*                                1  1    1  1   1   1  1  1
  String Date_time_line_count =  "L1:999 07/19/2020 14:12:08";
  String Date_time_line_count2 = "L2:888 07/19/2020 18:19:55";
  String Date_time_line_count3 = "L3:556 07/19/2020 11:12:33";
  String Date_time_line_count4 = "L4:777 07/19/2020 11:34:21";
*/
String DataStr = "02: 07/21/2020 01:24:14 1";
#include <Wire.h>
const byte rom = 0x50;    // Address of 24LC256 eeprom chip
int eeAddress = 100;

void setup (void)
{
  Serial.begin (19200);   // debugging
  Serial.println(); Serial.println();
  Wire.begin ();
byte Line=1;
//Serial.println(DataStr.substring(0,2));
//Line=(byte)DataStr.substring(0,2) ;


byte LineCount=199; //Макс 250

byte month=7;
byte day=19;
byte year=20;

byte hour=10;
byte min=11;
byte sec=45;
  // test: write the number 123 to address 0x1234
  /*
  writeEEPROM (rom, eeAddress, Line);
  eeAddress+=1;
  
  writeEEPROM (rom, eeAddress, LineCount);
  eeAddress+=1;

  writeEEPROM (rom, eeAddress, month);
  eeAddress+=1;
  
  writeEEPROM (rom, eeAddress, day);
  eeAddress+=1;

  writeEEPROM (rom, eeAddress, year);
  eeAddress+=1;
  
  writeEEPROM (rom, eeAddress, hour);
  eeAddress+=1;
  
  writeEEPROM (rom, eeAddress, min);
  eeAddress+=1;

  writeEEPROM (rom, eeAddress, sec);
  */
  // read back to confirm
  eeAddress=100;

  for(int i=0;i<15;i++){
    byte ReadLine = readEEPROM (rom, eeAddress);
  Serial.print (ReadLine, DEC);  // display to confirm
  Serial.print (" ");
  eeAddress+=1;
  
  int ReadLineCount = readEEPROM (rom, eeAddress);
  Serial.print (ReadLineCount, DEC);  // display to confirm
  Serial.print (" ");
  eeAddress+=1;
  
  byte ReadMonth = readEEPROM (rom, eeAddress);
  Serial.print (ReadMonth, DEC); 
  Serial.print (".");
  eeAddress+=1;

  byte ReadDay = readEEPROM (rom, eeAddress);
  Serial.print (ReadDay, DEC);
  Serial.print ("."); 
  eeAddress+=1;

  int ReadYear = readEEPROM (rom, eeAddress);
  Serial.print (ReadYear, DEC); 
  Serial.print (" ");
  eeAddress+=1;

  byte ReadHour = readEEPROM (rom, eeAddress);
  Serial.print (ReadHour, DEC);
  Serial.print (":"); 
  eeAddress+=1;

  byte ReadMin = readEEPROM (rom, eeAddress);
  Serial.print (ReadMin, DEC); 
  Serial.print (":"); 
  eeAddress+=1;

  byte ReadSec = readEEPROM (rom, eeAddress);
  Serial.println (ReadSec, DEC); 
  eeAddress+=1;
  }

  
  


/*
  // test: write a string to address 0x1000
  byte hello [] = "Hello, world!";

  writeEEPROM (rom, 1, hello, sizeof hello);

  // read back to confirm
  byte test [sizeof hello];
  byte err = readEEPROM (rom, 1, test, sizeof test);

  Serial.println ((char *) test);  // display to confirm
  Serial.print("sizeof (hello):"); Serial.println (sizeof (hello) );

  byte hello2 [] = "Ballo, qorld!";
  writeEEPROM (rom, 1+14, hello2, sizeof hello2);

  byte test2 [sizeof hello2];
  byte err2 = readEEPROM (rom, 1+14, test2, sizeof test2);
  Serial.println ((char *) test2);  // display to confirm
  */
}  // end of setup

void loop() {}  // no main loop


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
