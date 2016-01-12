This is a fork of Michael Duane C library Time functions, optimised for the Arduino AVR devices,
found in avr_libc version 1.8.0 and above.

It has been created to provide access to RTC capabilities on AVR devices with the ability to
connect a 32kHz watch crystal on Timer 2.

It is not compatible with the Arduino tones.h functions, as the tones library has not been
fully implemented to use another timer other than Timer 2.

## General

The implementation aspires to conform with ISO/IEC 9899 (C90). However, due to limitations of the
target processor and the nature of its development environment, a practical implementation must
of necessity deviate from the standard.

Section 7.23.2.1 clock()
The type clock_t, the macro CLOCKS_PER_SEC, and the function clock() are not implemented. We
consider these items belong to operating system code, or to application code when no operating
system is present.

Section 7.23.2.3 mktime()
The standard specifies that mktime() should return (time_t) -1, if the time cannot be represented.
This implementation always returns a 'best effort' representation.

Section 7.23.2.4 time()
The standard specifies that time() should return (time_t) -1, if the time is not available.
Since the application must initialize the time system, this functionality is not implemented.

Section 7.23.2.2, difftime()
Due to the lack of a 64 bit double, the function difftime() returns a long integer. In most cases
this change will be invisible to the user, handled automatically by the compiler.

Section 7.23.1.4 struct tm
Per the standard, struct tm->tm_isdst is greater than zero when Daylight Saving time is in effect.
This implementation further specifies that, when positive, the value of tm_isdst represents
the amount time is advanced during Daylight Saving time.

Section 7.23.3.5 strftime()
Only the 'C' locale is supported, therefore the modifiers 'E' and 'O' are ignored.
The 'Z' conversion is also ignored, due to the lack of time zone name.

In addition to the above departures from the standard, there are some behaviors which are different
from what is often expected, though allowed under the standard.

There is no 'platform standard' method to obtain the current time, time zone, or
daylight savings 'rules' in the AVR environment. Therefore the application must initialize
the time system with this information. The functions set_zone(), set_dst(), and
set_system_time() are provided for initialization. Once initialized, system time is maintained by
calling the function system_tick() at one second intervals.

Though not specified in the standard, it is often expected that time_t is a signed integer
representing an offset in seconds from Midnight Jan 1 1970... i.e. 'Unix time'. This implementation
uses an unsigned 32 bit integer offset from Midnight Jan 1 2000. The use of this 'epoch' helps to
simplify the conversion functions, while the 32 bit value allows time to be properly represented
until Tue Feb 7 06:28:15 2136 UTC. The macros UNIX_OFFSET and NTP_OFFSET are defined to assist in
converting to and from Unix and NTP time stamps.

Unlike desktop counterparts, it is impractical to implement or maintain the 'zoneinfo' database.
Therefore no attempt is made to account for time zone, daylight saving, or leap seconds in past dates.
All calculations are made according to the currently configured time zone and daylight saving 'rule'.

In addition to C standard functions, re-entrant versions of ctime(), asctime(), gmtime() and
localtime() are provided which, in addition to being re-entrant, have the property of claiming
less permanent storage in RAM. An additional time conversion, isotime() and its re-entrant version,
uses far less storage than either ctime() or asctime().

Along with the usual smattering of utility functions, such as is_leap_year(), this library includes
a set of functions related the sun and moon, as well as sidereal time functions.

## Reference Manual

http://www.nongnu.org/avr-libc/user-manual/group__avr__time.html

The tm structure contains a representation of time 'broken down' into components of the
Gregorian calendar.

The normal ranges of the elements of tm are..
```
tm_sec      seconds after the minute - [ 0 to 59 ]
tm_min      minutes after the hour - [ 0 to 59 ]
tm_hour     hours since midnight - [ 0 to 23 ]
tm_mday     day of the month - [ 1 to 31 ]
tm_wday     days since Sunday - [ 0 to 6 ]
tm_mon      months since January - [ 0 to 11 ]
tm_year     years since 2000
tm_yday     days since January 1 - [ 0 to 365 ]
tm_isdst    Daylight Saving Time flag *
```

## Compatibility

  * ATmega1284p @ 24.576MHz : Seeed Studio Goldilocks, Seeed Studio Goldilocks Analogue
  * ATmega2560 @ 16MHz : Arduino Mega, Arduino ADK
  * ATmega2560 @ 16MHz : Seeed Studio ADK

## Files & Configuration

* time.h : contains the definitions for all functions.
* setup_RTC_interrupt() : this initialises Timer2, and the "once per second" RTC interrupt.

Example code for basic functions below.

```
#include <Arduino.h>
#include <time.h>

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

  set_system_time( mktime( (ptm)&CurrTimeDate));
}

void loop() {
  // put your main code here, to run repeatedly:

  time_t currentTick;     // set up a location for the current time stamp.

  time((time_t *)&currentTick); // get the current time stamp.

  Serial.println(ctime( (time_t *)&currentTick));

  delay(2000);
}
```


