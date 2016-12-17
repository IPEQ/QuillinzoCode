/* $Id: Tone.h 113 2010-06-16 20:16:29Z bhagman@roguerobotics.com $

  A Tone Generator Library

  Written by Brett Hagman
  http://www.roguerobotics.com/
  bhagman@roguerobotics.com

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*************************************************/

#ifndef _Tone_h
#define _Tone_h

#include <stdint.h>
#include "Arduino.h"

class Tone {
  public:
    void begin(uint8_t tonePin);
    bool isPlaying();
    void play(uint16_t frequency, uint32_t duration = 0);
    void stop();

  private:
    static uint8_t _tone_pin_count;
    uint8_t _pin;
    int8_t _timer;
};

#endif
