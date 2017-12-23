// TODO: Update pin usage

/*
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
// # D35 -> Start alarm button
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
*/

// Headers
#include <Arduino.h>
// #include <setjmp.h> // For error handling only
#include <Tone.h>

// Degug code will only work when the line below is uncomented
#define DEBUG 0

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

#define BOARD_DEFINED   B10000000 // No board selected
#define BOARD_OVERLOAD  B01000000 // Multiple boards selected

#define ERROR_UNDEFINED 0x1
#define ERROR_OVERLOAD  0x2

// Only for testing
// bypass setup, example: ´#define BOARD BOARD_1´
#define BOARD 0

// Variabes
int boardSelectionPins [] = {7, 6, 5, 4};

bool runCode = false; // by default, just for safe measures, don't run any code

// pls fix this
// static jmp_buf jmpBuff; // Jmp buffer

unsigned long previousMillis = 0;
unsigned long interval = 0;

byte board;
byte boardList [] = {BOARD_1, BOARD_2, BOARD_3, BOARD_4};

Tone buzzer;
// Variables


// Functions
// ...
// TODO: Add sound functions here
// Functions

void setup () {
    board = B00000000; // Blank board

    pinMode (13, OUTPUT);
    digitalWrite (13, LOW);

    buzzer.begin (11);

    #if DEBUG == 1
    Serial.begin (9600);
    #endif // DEBUG

    #if BOARD == 0 // If the board is not defined by preprocessor

    // Set the pins for defining the board
    for (int i = 0; i < arraySize (boardSelectionPins); i++) {
        pinMode (boardSelectionPins [i], INPUT);
        #if DEBUG == 1
        Serial.print ("Arduino pin ");
        Serial.print (boardSelectionPins [i]);
        Serial.println (" programmed as INPUT");
        #endif // DEBUG
    }

    #if DEBUG == 1
    Serial.println ("---");
    #endif // DEBUG

    // Algorithm for board selection
    for (int i = 0; i < arraySize (boardSelectionPins); i++) {
        #if DEBUG == 1
        Serial.print ("Board -> ");
        Serial.println (board);

        Serial.print ("Arduino pin ");
        Serial.print (boardSelectionPins [i]);
        Serial.print (" is ");
        Serial.println (digitalRead (boardSelectionPins [i]));
        #endif // DEBUG

        // If the board is overloaded, break the for loop
        if (board & BOARD_OVERLOAD) break;

        // If a pin is selected
        if (digitalRead (boardSelectionPins [i])) {
            // If the board is not defined
            if (!(board & BOARD_DEFINED) && !(board & BOARD_OVERLOAD)) {
                // Define the board and mark it as 'defined'
                board |= boardList [i] | BOARD_DEFINED;

                #if DEBUG == 1
                Serial.println ("-> Board is defined!");
                #endif // DEBUG
            }
            // If the board is already defined
            else if (board & BOARD_DEFINED) {
                // Undefine the board
                board &= ~BOARD_DEFINED;

                // and mark it as 'overload'
                board |= BOARD_OVERLOAD;

                #if DEBUG == 1
                Serial.println ("-> The board is already defined!");
                #endif // DEBUG
            }
        }
        #if DEBUG == 1
        Serial.println ("");
        #endif
    }

    // Algorithm for error handling
    if (board & BOARD_OVERLOAD) {
        #if DEBUG == 1
        Serial.println ("Error: Board overload");
        #endif
        // Play sound of error overload, still testing tho
    }
    else if (!(board & BOARD_DEFINED)) {
        #if DEBUG == 1
        Serial.println ("Error: Board is undefined");
        #endif
        // Play the sound of an undefined board, still testing tho
    }
    else {
        #if DEBUG == 1
        Serial.println ("No error found!");
        Serial.print ("Board #");
        for (int i = 0; i < arraySize (boardSelectionPins); i++) {
            if (digitalRead(boardSelectionPins [i])) {
                Serial.print (i + 1);
                break;
            }
        }
        Serial.println (" selected!");
        #endif
        runCode = true;
        interval = 100;

        buzzer.play (700 , 150);
        delay (150);
        buzzer.play (830, 150);
        delay (150);
        buzzer.play (1050, 150);
    }

    // this switch must be of some help somewhere
    // need to fix this tho ('default' case not being detected at all)
    // technically, the 'default' case should be the 'unknow error',
    // and a special case where a 'board defined' is thrown. (contradictory to what error handling should be)

    /*
    switch (setjmp(jmpBuff)) {
        case 0: {
            #ifdef DEBUG
            Serial.println ("\'Try\' block running...");
            #endif

            // If the board presents overloaded pins
            if (board & BOARD_OVERLOAD)
                longjmp (jmpBuff, ERROR_OVERLOAD);}

            // Else, if the board present undefined pins
            else if (!(board & BOARD_DEFINED))
                longjmp (jmpBuff, ERROR_UNDEFINED);

            break;
        }
        case ERROR_OVERLOAD: {
            // Show that there is an overload
            #ifdef DEBUG
            Serial.println ("Error: Board overload");
            #endif
            // runCode = false;
            interval = 3000;
            break;
        }
        case ERROR_UNDEFINED: {
            // Show that the board is undefined
            #ifdef DEBUG
            Serial.println ("Error: Board is undefined");
            #endif
            // runCode = false;
            interval = 2000;
            break;
        }
        default: {
            Serial.println ("test");
            // Default code runs if no error is present
            #ifdef DEBUG
            Serial.println ("No error found!");
            Serial.print ("Board #");
            for (int i = 0; i < arraySize (boardSelectionPins); i++) {
                if (digitalRead(boardSelectionPins [i])) {
                    Serial.println (boardSelectionPins [i]);
                    break;
                }
            }
            // Serial.printLn (" selected");
            #endif
            // runCode = true;
            interval = 100;
            break;
        }
    } // Try - catch - trow
*/
    #endif // BOARD

    #if DEBUG == 1
    Serial.println ("Running code...");
    #endif // DEBUG

    // Do not press any button, not even the interrupts, until you hear the following sound
    {
        int duration = 150;
        int freq     = 830;

        buzzer.play (freq, duration);
        delay (duration * 2);
        buzzer.play (freq, duration);
        delay (duration * 2);
        buzzer.play (freq, duration);
        delay (duration * 2);
        buzzer.play (freq, duration);
    }
}

void loop () {
    if (runCode) {
        if (millis () - previousMillis > interval)
            digitalWrite(13, !digitalRead(13)), previousMillis = millis ();
    }
}
