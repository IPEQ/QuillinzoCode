#include <Arduino.h>

// ####
// # Arduino Mega 2560 pin configuration
// ####
// # D0  -> RX0                     *
// # D1  -> TX0                     *
// # D2  -> Interrupt 0 | PWM       *
// # D3  -> Interrupt 1 | PWM       *
// # D4  -> PWM                     *
// # D5  -> PWM                     *
// # D6  -> PWM                     *
// # D7  -> PWM                     *
// # D8  -> PWM                     *
// # D9  -> PWM                     *
// # D10 -> PWM                     *
// # D11 -> PWM                     *
// # D12 -> PWM                     *
// # D13 -> PWM                     *
// # D14 -> TX3                     *
// # D15 -> RX3                     *
// # D16 -> TX2                     *
// # D17 -> RX2                     *
// # D18 -> Interrupt 5 | TX1       *
// # D19 -> Interrupt 4 | RX1       *
// # D20 -> Interrupt 3 | SDA       *
// # D21 -> Interrupt 2 | SCL       *
// # D22 -> Jumper 1
// # D23 -> Jumper 2
// # D24 -> Jumper 3
// # D25 -> Jumper 4
// # D26 -> (74HC4511) pin 7
// # D27 -> (74HC4511) pin 1
// # D28 -> (74HC4511) pin 2
// # D29 -> (74HC4511) pin 6
// # D30 -> Decimal point
// # D31 ->                         *
// # D32 ->                         *
// # D33 ->                         *
// # D34 ->                         *
// # D35 ->                         *
// # D36 ->                         *
// # D37 ->                         *
// # D38 ->                         *
// # D39 ->                         *
// # D40 ->                         *
// # D41 ->                         *
// # D42 ->                         *
// # D43 ->                         *
// # D44 -> PWM                     *
// # D45 -> PWM                     *
// # D46 -> PWM                     *
// # D47 ->                         *
// # D48 ->                         *
// # D49 ->                         *
// # D50 -> MISO                    *
// # D51 -> MOSI                    *
// # D52 -> SCK                     *
// # D53 -> SS                      *
// ####
// # A0  ->                         *
// # A1  ->                         *
// # A2  ->                         *
// # A3  ->                         *
// # A4  ->                         *
// # A5  ->                         *
// # A6  ->                         *
// # A7  ->                         *
// # A8  ->                         *
// # A9  ->                         *
// # A10 ->                         *
// # A11 ->                         *
// # A12 ->                         *
// # A13 ->                         *
// # A14 ->                         *
// # A15 ->                         *
// ####

// Degug code will only work when the line below is uncomented
// #define DEBUG

// Return the size of the array
// Equivalent method: sizeof (arr) / sizeof (size_t);
template <class T, size_t tSize>
T arraySize (T (&array) [tSize] ) {
    return tSize;
}

#ifdef DEBUG
    #define BOARD 0 // Default board for debuging
#endif

int boardSelectionPins [] = {22, 23, 24, 25};

void setup () {
    #ifdef DEBUG
    Serial.begin (9600);
    #endif

    #ifdef BOARD

    #else
    // If no default board was defined...
    for (int i = 0; i < arraySize (boardSelectionPins); i++) {
        pinMode (boardSelectionPins [i], INPUT);
    }

    int temp = 0;
    for (int i = 0; i < arraySize(boardSelectionPins); i++)
        temp += digitalRead(boardSelectionPins [i]);

    if (temp > 1){
        // Overload
    }
    else if (temp < 1) {
        // no jumpers placed
    }
    else {
        // unknow error
    }
    #endif

}

void loop () {

}
