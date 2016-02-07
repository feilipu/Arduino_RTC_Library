#include <Arduino.h>

#include <time.h>

void setup() {
  // put your setup code here, to run once:
  setup_RTC_interrupt();
  Serial.begin(38400);      // open the serial port at 9600 bps:

  tm CurrTimeDate;       // set up an array for the RTC info.
                         // <year yyyy> <month mm Jan=0> <date dd> <day d Sun=0> <hour hh> <minute mm> <second ss>

  CurrTimeDate.tm_year = (uint8_t)(   2016 - 1900 );
  CurrTimeDate.tm_mon = (uint8_t)     0;
  CurrTimeDate.tm_mday = (uint8_t)    12;
  CurrTimeDate.tm_wday = (uint8_t)    2;
  CurrTimeDate.tm_hour = (uint8_t)    17;
  CurrTimeDate.tm_min = (uint8_t)     16;
  CurrTimeDate.tm_sec = (uint8_t)     0;

  set_system_time( mktime( (ptm)&CurrTimeDate));
}

void loop() {
  // put your main code here, to run repeatedly:

  time_t currentTick;     // set up a location for the current time stamp since the 

  time((time_t *)&currentTick);

  Serial.println(ctime( (time_t *)&currentTick));

  delay(2000);

}
