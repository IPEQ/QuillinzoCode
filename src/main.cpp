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
// # D31 -> PIR #1
// # D32 -> PIR #2
// # D33 -> Ultrasonic trigger
// # D34 -> Ultrasonic echo
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

// Headers
#include <Arduino.h>
#include <setjmp.h>

// Degug code will only work when the line below is uncomented
// #define DEBUG

// Return the size of the array
// Equivalent method: sizeof (arr) / sizeof (size_t);
template <class T, size_t tSize>
T arraySize (T (&array) [tSize] ) {
    return tSize;
}

// Flags         12345678
#define BOARD_1 B00000001 // 1
#define BOARD_2 B00000010 // 2
#define BOARD_3 B00000100 // 4
#define BOARD_4 B00001000 // 8

// #define BOARD_TEMPLATE B00000000

#define BOARD_DEFINED B10000000 // No board selected
#define BOARD_OVERLOAD  B01000000 // Multiple boards selected


#ifdef DEBUG
#define BOARD 0 // Default board for debuging
#endif

int boardSelectionPins [] = {22, 23, 24, 25};

byte board;
byte boardList [] = {BOARD_1, BOARD_2, BOARD_3, BOARD_4};

void setup () {
    board = B00000000; // Blank definition

    #ifdef DEBUG
    Serial.begin (9600);
    #endif

    #ifndef BOARD
    // If no default board was defined...
    // Set the pins for defining the board
    for (int i = 0; i < arraySize (boardSelectionPins); i++)
        pinMode (boardSelectionPins [i], INPUT);

    for (int i = 0; i < arraySize (boardSelectionPins); i++) {
        // This seems to work better
        if (digitalRead(boardSelectionPins [i])) {
            // If the board is not defined and there is a pin defined, then define the board and mark the board based in th eboard list
            if (!(board & BOARD_DEFINED)) board |= (BOARD_DEFINED | boardList [i]);
            else board |= BOARD_OVERLOAD; // If the board is already defined and there is another pin defined, then is an overload
        }
            // board |= boardList [i]; // this seems to work I gues
    }

    #endif
}

void loop () {

}
