This library has been created to provide RTC capabilities on AVR devices with the ability to connect a 32kHz watch crystal on Timer 2, such as the Goldilocks ATMega1284p, and the Arduino Mega ATmega2560.

It is not compatible with the Arduino tones.h functions, as the tones library has not been fully implemented to use another timer other than Timer 2.

## General

The AVR standard time implementation aspires to conform with ISO/IEC 9899 (C90). However, due to limitations of the target processor and the nature of its development environment, a practical implementation must of necessity deviate from the standard.

## Reference Manual

http://www.nongnu.org/avr-libc/user-manual/group__avr__time.html

The tm structure contains a representation of time 'broken down' into components of the Gregorian calendar.

The normal ranges of the elements of tm are...
```
tm_sec      seconds after the minute - [ 0 to 59 ]
tm_min      minutes after the hour - [ 0 to 59 ]
tm_hour     hours since midnight - [ 0 to 23 ]
tm_mday     day of the month - [ 1 to 31 ]
tm_wday     days since Sunday - [ 0 to 6 ]
tm_mon      months since January - [ 0 to 11 ]
tm_year     years since 2000
tm_yday     days since January 1 - [ 0 to 365 ]
tm_isdst    Daylight Saving Time flag
```

## Compatibility

  * ATmega1284p @ 24.576MHz : Seeed Studio Goldilocks, Seeed Studio Goldilocks Analogue
  * ATmega2560 @ 16MHz : Arduino Mega, Arduino ADK
  * ATmega2560 @ 16MHz : Seeed Studio ADK

## Files & Configuration

* AVR_RTC.h : contains the definitions for all functions.
* setup_RTC_interrupt() : this initialises Timer2, and the "once per second" RTC interrupt.

Example code for basic functions below.

```
#include <AVR_RTC.h>

void setup() {
  // put your setup code here, to run once:

  setup_RTC_interrupt(); // initialise the RTC.

  Serial.begin(38400);   // open the serial port at 38400 bps.

  tm CurrTimeDate;       // set up an array for the RTC info.
                         // <year yyyy> <month mm Jan=0> <date dd> <day d Sun=0> <hour hh> <minute mm> <second ss>

  CurrTimeDate.tm_year = (uint8_t)(   2016 - 1900 );
  CurrTimeDate.tm_mon = (uint8_t)     0;
  CurrTimeDate.tm_mday = (uint8_t)    12;
  CurrTimeDate.tm_wday = (uint8_t)    2;
  CurrTimeDate.tm_hour = (uint8_t)    17;
  CurrTimeDate.tm_min = (uint8_t)     16;
  CurrTimeDate.tm_sec = (uint8_t)     0;

  set_system_time( mktime( (tm*)&CurrTimeDate ) );
}

void loop() {
  // put your main code here, to run repeatedly:

  time_t currentTick;     // set up a location for the current time stamp.

  time((time_t *)&currentTick); // get the current time stamp.

  Serial.println(ctime( (time_t *)&currentTick));

  delay(2000);
}
```

