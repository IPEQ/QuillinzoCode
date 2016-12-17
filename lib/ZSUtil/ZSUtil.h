#ifndef _ZSUTIL_H_
#define _ZSUTIL_H_

// Arduino library
#include "Arduino.h"
#include "Tone.h"

// C Standar int types
#include <stdint.h>


// Namespace of the library
namespace ZSUtil {
    class Led {
    private:
        void _updateStatus ();

        uint64_t _previousMillis;
        uint32_t _onTime;
        uint32_t _offTime;
        uint8_t  _pin;
        int      _ledState;


    public: // Create all constructors later
        void begin         (uint8_t  pin);
        void beginBlink    (uint8_t pin, uint32_t onTime, uint32_t offTime);
        void turnOn        ();
        void turnOff       ();
        void update        ();
        void setNewOnTime  (uint32_t newTime);
        void setNewOffTime (uint32_t newTime);
    };


    class Buzzer {
    private:
        uint64_t _previousMillis;
        uint32_t _onTime;
        uint32_t _offTime;
        uint16_t _frequency;
        uint8_t  _pin;
        bool     _isAlarm;
        bool     _stop;
        int      _buzzerState;
        Tone     _buzzer;

    public:
        void begin        (uint8_t pin, uint16_t frequency = 523);
        void beginAlarm   (uint8_t pin, uint32_t onTime, uint32_t offTime, uint16_t frequency = 523);
        void setFrequency (uint16_t frequency);
        void update       ();
        void stop         ();
        void play         ();
    };
} /* ZSUtil */
#endif
