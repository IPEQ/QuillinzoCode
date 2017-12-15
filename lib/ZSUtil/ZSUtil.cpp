// Arduino library
#include "Arduino.h"

// Needed libraryes
#include "ZSUtil.h"

// C Standar int types
#include <stdint.h>


// namespace of the library
namespace ZSUtil { // Create all constructors
    void Led::_updateStatus () { digitalWrite(_pin, _ledState); }
    void Led::begin (uint8_t pin) {
        _pin = pin;

        // Arduino setup
        _ledState = LOW;
        pinMode (_pin, OUTPUT);
    }
    void Led::beginBlink (uint8_t pin, uint32_t onTime, uint32_t offTime) {
        // Setup
        _onTime  = onTime;
        _offTime = offTime;
        _pin     = pin;

        // Arduino setup
        _ledState = LOW;
        pinMode (_pin, OUTPUT);
    }

    void Led::turnOn () {
        _ledState = HIGH;
        _updateStatus ();
    }
    void Led::turnOff () {
        _ledState = LOW;
        _updateStatus ();
    }
    void Led::update () {
        uint64_t currentMillis = millis ();

        if ((_ledState == HIGH) && (currentMillis - _previousMillis > _onTime)) {
            _previousMillis = currentMillis;
            _ledState = LOW;
            _updateStatus ();
        }
        else if ((_ledState == LOW) && (currentMillis - _previousMillis > _offTime)) {
            _previousMillis = currentMillis;
            _ledState = HIGH;
            _updateStatus ();
        }

    }
    void Led::setNewOnTime  (uint32_t newTime) { _onTime = newTime; }
    void Led::setNewOffTime (uint32_t newTime) { _offTime = newTime; }


    void Buzzer::begin (
        uint8_t pin,
        uint16_t frequency
    ) {
        _buzzer.begin (pin);

        _buzzerState = LOW;
        _isAlarm     = false;
        _stop        = false;
        _frequency   = frequency;
    }
    void Buzzer::beginAlarm (
        uint8_t pin,
        uint32_t onTime,
        uint32_t offTime,
        uint16_t frequency
    ) {
        _buzzer.begin (pin);

        _onTime = onTime;
        _offTime = offTime;

        _buzzerState = LOW;
        _isAlarm     = true;
        _stop        = false;
        _frequency   = frequency;
    }

    void Buzzer::setFrequency (uint16_t frequency) { _frequency = frequency; }
    void Buzzer::stop ()                           { _buzzer.stop (); _stop = true; }
    void Buzzer::play ()                           { _stop = false; }
    void Buzzer::update () {
        if (!_stop) {
            if (_isAlarm) {
                uint64_t currentMillis = millis ();

                if (_buzzer.isPlaying () && (currentMillis - _previousMillis > _onTime)) {
                    _previousMillis = currentMillis;
                    _buzzer.stop ();
                }
                if (!_buzzer.isPlaying () && (currentMillis - _previousMillis > _offTime)) {
                    _previousMillis = currentMillis;
                    _buzzer.play (_frequency);
                }
            }
            else _buzzer.play (_frequency);
        }
        else _buzzer.stop ();
    }
} /* ZSUtil */
