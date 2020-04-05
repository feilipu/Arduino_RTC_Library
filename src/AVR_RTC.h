/*
 * (C)2020 Phillip Stevens All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. Redistributions in binary
 * form must reproduce the above copyright notice, this list of conditions
 * and the following disclaimer in the documentation and/or other materials
 * provided with the distribution. Neither the name of the copyright holders
 * nor the names of contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AVR_RTC_H
#define AVR_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

    /**
        The tm structure contains a representation of time 'broken down' into components of the
        Gregorian calendar.

        The normal ranges of the elements are..

    \code
        tm_sec      seconds after the minute - [ 0 to 59 ]
        tm_min      minutes after the hour - [ 0 to 59 ]
        tm_hour     hours since midnight - [ 0 to 23 ]
        tm_mday     day of the month - [ 1 to 31 ]
        tm_wday     days since Sunday - [ 0 to 6 ]
        tm_mon      months since January - [ 0 to 11 ]
        tm_year     years since 2000
        tm_yday     days since January 1 - [ 0 to 365 ]
        tm_isdst    Daylight Saving Time flag *

    \endcode

        *The value of tm_isdst is zero if Daylight Saving Time is not in effect, and is negative if
        the information is not available.

        When Daylight Saving Time is in effect, the value represents the number of
        seconds the clock is advanced.
    */

    typedef struct tm tm;

    /**
        Convert a Y2K time stamp into a FAT file system time stamp.
    */
    uint32_t system_fatfs(const struct tm * timeptr);

    /**
        Convert a FAT file system time stamp into a Y2K time stamp.
    */
    uint32_t fatfs_system( uint16_t fsdate, uint16_t fstime, struct tm * timeptr);

    /**
        * Perform hardware setup to enable 1 second sys_tick() from RTC on Timer 2.
    */
    void setup_RTC_interrupt( void );

#ifdef __cplusplus
}
#endif

#endif  /* AVR_RTC_H  */
